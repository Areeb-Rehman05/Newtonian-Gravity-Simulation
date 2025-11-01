#include <SDLWrapper/VectorPreview.h>

VectorPreview::VectorPreview() {

}

VectorPreview::~VectorPreview() {

}

void VectorPreview::init(int x, int y, int w, int h) {
    previewRect = {x, y, w, h};
} 

void VectorPreview::updateData(std::vector<Body> bodies) {
    bodyData = bodies;

    double maxCoord = 100;
    for (auto& body : bodyData) {
        Eigen::Vector2d pos = body.getPosition();
        maxCoord = std::max({maxCoord, std::abs(pos.x()), std::abs(pos.y())});
    }
    scale = maxCoord;
}

void VectorPreview::render(SDL_Renderer* renderer) {
    // Draw axes
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, previewRect.x, previewRect.y + previewRect.h / 2, previewRect.x + previewRect.w, previewRect.y + previewRect.h / 2);
    SDL_RenderDrawLine(renderer, previewRect.x + previewRect.w / 2, previewRect.y, previewRect.x + previewRect.w / 2, previewRect.y + previewRect.h);

    double velocityScale = previewRect.w * 0.01;
    double minLength = 8.0; // Minimum visible vector length

    int count = 0;

    for (auto& body : bodyData) {
        count++;
        Eigen::Vector2d pos = body.getPosition();
        Eigen::Vector2d vel = body.getVelocity();

        int previewX = previewRect.x + previewRect.w / 2 + static_cast<int>((pos.x() / scale) * previewRect.w / 2);
        int previewY = previewRect.y + previewRect.h / 2 - static_cast<int>((pos.y() / scale) * previewRect.h / 2);

        int bodySize = (body.mass / scale) + 4;
        SDL_Rect bodyRect = {previewX - (bodySize / 2), previewY - (bodySize / 2), bodySize, bodySize};

        SDL_SetRenderDrawColor(renderer, bodyColors[count % 7].r, bodyColors[count % 7].g, bodyColors[count % 7].b, bodyColors[count % 7].a);
        SDL_RenderFillRect(renderer, &bodyRect);

        double velMag = vel.norm();
        if (velMag > 0.0001) {
            Eigen::Vector2d velDir = vel.normalized();

            double scaledLength = std::max(minLength, velocityScale * std::log1p(velMag));
            int previewVelx = static_cast<int>(velDir.x() * scaledLength);
            int previewVely = static_cast<int>(-velDir.y() * scaledLength);

            // Start from edge of body
            int startX = previewX + static_cast<int>(velDir.x() * (bodySize / 2.0));
            int startY = previewY - static_cast<int>(velDir.y() * (bodySize / 2.0));

            // Draw velocity line
            SDL_RenderDrawLine(renderer, startX, startY, startX + previewVelx, startY + previewVely);

            // Draw arrowhead
            double arrowAngle = atan2(previewVely, previewVelx);
            int arrowLen = 6;

            int x1 = startX + previewVelx - static_cast<int>(arrowLen * cos(arrowAngle - M_PI / 6));
            int y1 = startY + previewVely - static_cast<int>(arrowLen * sin(arrowAngle - M_PI / 6));
            int x2 = startX + previewVelx - static_cast<int>(arrowLen * cos(arrowAngle + M_PI / 6));
            int y2 = startY + previewVely - static_cast<int>(arrowLen * sin(arrowAngle + M_PI / 6));

            SDL_RenderDrawLine(renderer, startX + previewVelx, startY + previewVely, x1, y1);
            SDL_RenderDrawLine(renderer, startX + previewVelx, startY + previewVely, x2, y2);
        }
    }
}

void VectorPreview::free() {
    bodyData.clear();
}

int VectorPreview::getScale() {
    return scale;
}