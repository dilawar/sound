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

#include "gnuplot-iostream.h"
#include <boost/tuple/tuple.hpp>
#include <map>

template<typename T>
void plot(map<string, T>& dataMap, string filename = "")
{
    DUMP("Plotting to " << filename, "DEBUG");
    Gnuplot gp;

}

void plotXY(vector<double> xData, vector<double> yData, bool plotToFile = false)
{
    DUMP("Plotting using gnuplot", "DEBUG");
    Gnuplot gp;

    gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
    gp << "plot '-' with lines" << endl;
    gp.send1d(boost::make_tuple(xData, yData));
}
#endif   /* ----- #ifndef PLOT_INC  ----- */
