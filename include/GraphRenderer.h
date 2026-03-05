#ifndef GRAPH_RENDERER_H
#define GRAPH_RENDERER_H

#include "FCSDataModel.h"
#include <string>
#include <vector>

class GraphRenderer {
public:
    GraphRenderer();
    ~GraphRenderer();
    
    // Rendering methods
    bool renderScatterPlot(const FCSDataModel* data, 
                          int paramX, int paramY, 
                          const std::string& outputFile);
    
    bool renderHistogram(const FCSDataModel* data, 
                        int paramIndex, 
                        const std::string& outputFile);
    
    bool render2DPlot(const FCSDataModel* data, 
                     int paramX, int paramY, int paramZ,
                     const std::string& outputFile);
    
private:
    // Helper methods for ASCII visualization
    void drawASCIIScatter(const std::vector<double>& xData,
                          const std::vector<double>& yData);
    
    void drawASCIIHistogram(const std::vector<double>& data, int bins = 50);
    
    static constexpr int PLOT_WIDTH = 80;
    static constexpr int PLOT_HEIGHT = 20;
};

#endif // GRAPH_RENDERER_H