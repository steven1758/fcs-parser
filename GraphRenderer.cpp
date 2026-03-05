#include "GraphRenderer.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

GraphRenderer::GraphRenderer() {}

GraphRenderer::~GraphRenderer() {}

bool GraphRenderer::renderScatterPlot(const FCSDataModel* data,  
                                     int paramX, int paramY,  
                                     const std::string& outputFile) {
    if (!data || paramX >= data->getParameterCount() || paramY >= data->getParameterCount()) {
        return false;
    }
    
    std::vector<double> xData, yData;
    
    for (const auto& event : data->getEvents()) {
        if (paramX < event.parameters.size() && paramY < event.parameters.size()) {
            xData.push_back(event.parameters[paramX]);
            yData.push_back(event.parameters[paramY]);
        }
    }
    
    drawASCIIScatter(xData, yData);
    return true;
}

bool GraphRenderer::renderHistogram(const FCSDataModel* data,  
                                   int paramIndex,  
                                   const std::string& outputFile) {
    if (!data || paramIndex >= data->getParameterCount()) {
        return false;
    }
    
    std::vector<double> paramData;
    
    for (const auto& event : data->getEvents()) {
        if (paramIndex < event.parameters.size()) {
            paramData.push_back(event.parameters[paramIndex]);
        }
    }
    
    drawASCIIHistogram(paramData);
    return true;
}

bool GraphRenderer::render2DPlot(const FCSDataModel* data,  
                               int paramX, int paramY, int paramZ,
                               const std::string& outputFile) {
    return renderScatterPlot(data, paramX, paramY, outputFile);
}

void GraphRenderer::drawASCIIScatter(const std::vector<double>& xData,
                                    const std::vector<double>& yData) {
    if (xData.empty() || yData.empty()) return;
    
    auto minMaxX = std::minmax_element(xData.begin(), xData.end());
    auto minMaxY = std::minmax_element(yData.begin(), yData.end());
    
    double xMin = *minMaxX.first;
    double xMax = *minMaxX.second;
    double yMin = *minMaxY.first;
    double yMax = *minMaxY.second;
    
    std::vector<std::vector<int>> grid(PLOT_HEIGHT, std::vector<int>(PLOT_WIDTH, 0));
    
    for (size_t i = 0; i < xData.size(); ++i) {
        int x = static_cast<int>((xData[i] - xMin) / (xMax - xMin) * (PLOT_WIDTH - 1));
        int y = static_cast<int>((yData[i] - yMin) / (yMax - yMin) * (PLOT_HEIGHT - 1));
        
        x = std::max(0, std::min(x, PLOT_WIDTH - 1));
        y = std::max(0, std::min(y, PLOT_HEIGHT - 1));
        
        grid[PLOT_HEIGHT - 1 - y][x]++;
    }
    
    std::cout << "\n=== Scatter Plot ===" << std::endl;
    for (const auto& row : grid) {
        for (int cell : row) {
            std::cout << (cell > 0 ? '*' : ' ');
        }
        std::cout << std::endl;
    }
    std::cout << "\nX-axis: " << xMin << " to " << xMax << std::endl;
    std::cout << "Y-axis: " << yMin << " to " << yMax << std::endl;
}

void GraphRenderer::drawASCIIHistogram(const std::vector<double>& data, int bins) {
    if (data.empty()) return;
    
    auto minMax = std::minmax_element(data.begin(), data.end());
    double minVal = *minMax.first;
    double maxVal = *minMax.second;
    
    std::vector<int> histogram(bins, 0);
    
    for (double value : data) {
        int binIndex = static_cast<int>((value - minVal) / (maxVal - minVal) * (bins - 1));
        binIndex = std::max(0, std::min(binIndex, bins - 1));
        histogram[binIndex]++;
    }
    
    int maxCount = *std::max_element(histogram.begin(), histogram.end());
    
    std::cout << "\n=== Histogram ===" << std::endl;
    for (int i = 0; i < bins; ++i) {
        int barLength = static_cast<int>(histogram[i] * PLOT_WIDTH / maxCount);
        std::cout << std::setw(3) << i << " |";
        for (int j = 0; j < barLength; ++j) {
            std::cout << '#';
        }
        std::cout << " (" << histogram[i] << ")" << std::endl;
    }
}