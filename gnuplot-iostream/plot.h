/*
 * ==============================================================================
 *
 *       Filename:  plot.h
 *
 *    Description:  Function to plot using gnuplot.
 *
 *        Version:  1.0
 *        Created:  11/24/2014 07:13:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dilawar Singh (), dilawars@ncbs.res.in
 *   Organization:  
 *
 * ==============================================================================
 */

#ifndef  PLOT_INC
#define  PLOT_INC

#include <map>
#include <vector>
#include <fstream>
#include <iostream>

void plotXY(vector<double>& xData, map<string, vector<double>>& mapData
        , string filename = ""
        )
{
    stringstream plotSS;
    unsigned columnNos = mapData.size();
    vector<string> columnNames;

    for(auto it : mapData) columnNames.push_back(it->first);

    for(size_t i = 0; i < xData.size(); i++)
        plotSS << xData[i] << "," << yData[i] << endl;

    if(filename.size() == 0)
        cout << plotSS.str();
    else
    {
        ofstream outF;
        outF.open(filename);
        outF << plotSS.str();
        outF.close();
    }
    DUMP("Done writing data to " << filename, "INFO");
}
#endif   /* ----- #ifndef PLOT_INC  ----- */
