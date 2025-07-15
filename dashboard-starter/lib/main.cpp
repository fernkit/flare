#include <fern/fern.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace Fern;

// Dashboard data structures
struct MetricCard {
    std::string title;
    std::string value;
    std::string change;
    uint32_t color;
    float x, y, width, height;
};

struct ChartData {
    std::string label;
    float value;
    uint32_t color;
};

// Sample data
std::vector<MetricCard> metrics = {
    {"Active Users", "2,547", "+12%", Colors::Green, 50, 80, 180, 100},
    {"Revenue", "$45,230", "+8%", Colors::Blue, 250, 80, 180, 100},
    {"Orders", "1,234", "+15%", Colors::Orange, 450, 80, 180, 100},
    {"Conversion", "3.2%", "-2%", Colors::Red, 650, 80, 180, 100}
};

std::vector<ChartData> chartData = {
    {"Desktop", 45.0f, Colors::Blue},
    {"Mobile", 35.0f, Colors::Green},
    {"Tablet", 20.0f, Colors::Orange}
};

void drawMetricCard(const MetricCard& card) {
    // Card background
    Draw::rect(card.x, card.y, card.width, card.height, Colors::White);
    
    // Card border (simplified)
    Draw::line(card.x, card.y, card.x + card.width, card.y, 1, Colors::Gray);
    Draw::line(card.x, card.y, card.x, card.y + card.height, 1, Colors::Gray);
    Draw::line(card.x + card.width, card.y, card.x + card.width, card.y + card.height, 1, Colors::Gray);
    Draw::line(card.x, card.y + card.height, card.x + card.width, card.y + card.height, 1, Colors::Gray);
    
    // Title
    DrawText::drawText(card.title.c_str(), card.x + 10, card.y + 10, 1, Colors::DarkGray);
    
    // Value
    DrawText::drawText(card.value.c_str(), card.x + 10, card.y + 35, 2, Colors::Black);
    
    // Change indicator
    DrawText::drawText(card.change.c_str(), card.x + 10, card.y + 65, 1, card.color);
}

void drawBarChart(float x, float y, float width, float height) {
    float barWidth = width / chartData.size();
    float currentX = x;
    
    // Draw background
    Draw::rect(x, y, width, height, Colors::LightGray);
    
    for (const auto& data : chartData) {
        float barHeight = (data.value / 100.0f) * height;
        
        // Draw bar
        Draw::rect(currentX, y + height - barHeight, barWidth - 10, barHeight, data.color);
        
        // Draw label
        DrawText::drawText(data.label.c_str(), currentX + 5, y + height + 10, 1, Colors::Black);
        
        // Draw value percentage
        std::string valueText = std::to_string((int)data.value) + "%";
        DrawText::drawText(valueText.c_str(), currentX + 5, y + height - barHeight - 20, 1, Colors::Black);
        
        currentX += barWidth;
    }
}

void drawLegend(float x, float y) {
    float currentY = y;
    
    for (const auto& data : chartData) {
        // Color indicator
        Draw::rect(x, currentY, 15, 15, data.color);
        
        // Label with percentage
        std::string legendText = data.label + " (" + std::to_string((int)data.value) + "%)";
        DrawText::drawText(legendText.c_str(), x + 25, currentY + 2, 1, Colors::Black);
        
        currentY += 25;
    }
}

void draw() {
    // Clear background
    Draw::fill(Colors::White);
    
    // Header
    Draw::rect(0, 0, 800, 60, Colors::DarkBlue);
    DrawText::drawText("Dashboard Analytics", 20, 20, 3, Colors::White);
    
    // Draw metric cards
    for (const auto& card : metrics) {
        drawMetricCard(card);
    }
    
    // Charts section
    DrawText::drawText("Traffic Sources", 50, 220, 2, Colors::Black);
    
    // Bar chart
    drawBarChart(350, 250, 300, 120);
    
    // Legend
    drawLegend(50, 280);
    
    // Recent activity section
    DrawText::drawText("Recent Activity", 50, 420, 2, Colors::Black);
    
    // Activity list
    std::vector<std::string> activities = {
        "User john@example.com logged in",
        "New order #1234 placed",
        "Payment of $299.99 processed",
        "User profile updated",
        "Export completed"
    };
    
    float activityY = 450;
    for (const auto& activity : activities) {
        std::string activityText = "• " + activity;
        DrawText::drawText(activityText.c_str(), 50, activityY, 1, Colors::DarkGray);
        activityY += 20;
    }
    
    // Footer
    DrawText::drawText("Last updated: 2024-01-15 14:30", 50, 580, 1, Colors::Gray);
}

int main() {
    std::cout << "Starting Dashboard Starter - Analytics Dashboard..." << std::endl;
    
    // Initialize Fern
    Fern::initialize();
    
    // Set up render callback
    Fern::setDrawCallback(draw);
    
    // Start the application
    Fern::startRenderLoop();
    
    return 0;
}

