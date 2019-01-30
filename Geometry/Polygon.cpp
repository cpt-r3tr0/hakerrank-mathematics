#include <iostream>  // cin, istream, cout, endl
#include <cassert>   // assert
#include <vector>    // vector
#include <map>       // multimap, map
#include <algorithm> // sort
#include <fstream>   // ifstream


class Point2D
{
public:
    Point2D(double xx = 0, double yy = 0) : x(xx), y(yy) {}

public:
    double x;
    double y;
};


int main()
{

//#define USE_FILE
#ifdef USE_FILE
    std::ifstream inOutFile("C:\\E\\Python\\HackerRank\\MathGeometry\\Polygon\\output5.txt");
    std::istream & inOutStream = inOutFile;

    std::ifstream inFile("C:\\E\\Python\\HackerRank\\MathGeometry\\Polygon\\input5.txt");
    std::istream & inStream = inFile;

    //std::ofstream outFile("C:\\E\\Python\\HackerRank\\MathGeometry\\Polygon\\myOutput.txt");
    //std::ostream & outStream = outFile;

    std::ostream & outStream = std::cout;
#else
    std::istream & inStream = std::cin;
    std::ostream & outStream = std::cout;
#endif


    int numPoints, numQueries;
    inStream >> numPoints >> numQueries;
    inStream.ignore();
    assert((1 <= numPoints) && (numPoints <= 2e+4));
    assert((1 <= numQueries) && (numQueries <= 2e+4));

    std::vector<Point2D> points;
    points.reserve(numPoints);
    for (int i = 0; i < numPoints; ++i)
    {
        long long int x, y;
        inStream >> x >> y;
        inStream.ignore();
        assert((-2e+5 <= x) && (x <= 2e+5));
        assert((-2e+5 <= y) && (y <= 2e+5));
        points.emplace_back(x, y);
    }

    std::sort(points.begin(), points.end(),
        [] (const Point2D & p1, const Point2D & p2) { return ((p1.x < p2.x) || ((p1.x == p2.x) && (p1.y < p2.y))); });

    std::vector<long long int> pointXs(numPoints);
    std::vector<long long int> pointYs(numPoints);
    for (int i = 0; i < numPoints; ++i)
    {
        pointXs[i] = points[i].x;
        pointYs[i] = points[i].y;
    }
    points.clear();

    std::vector<long long int> answers;
    answers.reserve(numPoints);

    for (int i = 0; i < numQueries; ++i)
    {
        long long int numEdges;
        inStream >> numEdges;
        inStream.ignore();
        assert((4 <= numEdges) && (numEdges <= 20));

        std::multimap<long long int, long long int> xs;

        long long int prevX, prevY;
        inStream >> prevX >> prevY;
        inStream.ignore();
        assert((-2e+5 <= prevX) && (prevX <= 2e+5));
        assert((-2e+5 <= prevY) && (prevY <= 2e+5));
        auto firstX = prevX;
        auto firstY = prevY;

        long long int currX, currY;
        inStream >> currX >> currY;
        inStream.ignore();
        assert((-2e+5 <= currX) && (currX <= 2e+5));
        assert((-2e+5 <= currY) && (currY <= 2e+5));
        auto secondX = currX;
        auto secondY = currY;

        for (int j = 2; j < numEdges; ++j)
        {
            long long int nextX, nextY;
            inStream >> nextX >> nextY;
            inStream.ignore();
            assert((-2e+5 <= nextX) && (nextX <= 2e+5));
            assert((-2e+5 <= nextY) && (nextY <= 2e+5));

            // Store only non-trivial edges, i.e., skip edges whose two
            // endpoints coincide. Do not copy the middle vertex when three
            // consecutive vertices are on the same line.
            if ( ((prevX == currX) && (currX == nextX)) || ((prevY == currY) && (currY == nextY)) )
                continue;

            xs.insert(std::make_pair(currX, currY));
            prevX = currX;
            currX = nextX;
            prevY = currY;
            currY = nextY;
        }
        // Store the last vertex if appropriate.
        if (!(((prevX == currX) && (currX == firstX)) || ((prevY == currY) && (currY == firstY))))
            xs.insert(std::make_pair(currX, currY));
        prevX = currX;
        currX = firstX;
        prevY = currY;
        currY = firstY;

        // Store the first vertex if appropriate.
        if (!(((prevX == currX) && (currX == secondX)) || ((prevY == currY) && (currY == secondY))))
            xs.insert(std::make_pair(currX, currY));

        numEdges = xs.size();

        std::map<long long int, long long int> activeYs;
        std::vector<long long int> yToCheck;
        std::vector<long long int> yToReCheck;

        long long int numPointsInside = 0;
        long long int maxX = xs.begin()->first;

        auto xBeginPointToCheckIt = pointXs.begin();
        auto xEndPointToCheckIt = pointXs.begin();
        auto yBeginPointToCheckIt = pointYs.begin();
        auto yEndPointToCheckIt = pointYs.begin();

        //=================================================================
        // Points on the line of the left-most vertical edge.
        //=================================================================
        // Get the points at the line of the left-most vertical edge.
        xBeginPointToCheckIt = std::lower_bound(pointXs.begin(), pointXs.end(), maxX);
        xEndPointToCheckIt = std::upper_bound(xBeginPointToCheckIt, pointXs.end(), maxX);

        int numPointsToCheck = std::distance(xBeginPointToCheckIt, xEndPointToCheckIt);
        yBeginPointToCheckIt = pointYs.begin() + std::distance(pointXs.begin(), xBeginPointToCheckIt);
        yEndPointToCheckIt = yBeginPointToCheckIt + numPointsToCheck;

        // Copy the y values of the test points whose x values are equal to
        // maxX, and sort them.
        yToReCheck.resize(numPointsToCheck);
        std::copy(yBeginPointToCheckIt, yEndPointToCheckIt, yToReCheck.begin());
        std::sort(yToReCheck.begin(), yToReCheck.end());

        while (xs.empty() == false)
        {
            long long int minX = maxX;
            auto nextValueIt = xs.upper_bound(minX);
            if (nextValueIt == xs.end())
                break;
            // Get all new y's.
            for (auto it = xs.begin(); it != nextValueIt; ++it)
            {
                auto activeYsIt = activeYs.find(it->second);
                if (activeYsIt == activeYs.end())
                    activeYs[it->second] = it->first;
                else
                    activeYs.erase(activeYsIt);
            }
            // Get the upper/right bound in x for the current vertical sweep.
            maxX = nextValueIt->first;
            // Get rid of the polygon vertices just reached.
            xs.erase(xs.begin(), nextValueIt);



            //=================================================================
            // Points on a line of a vertical edge, re-checked from the right.
            //=================================================================
            // Skip the points outside and count the points inside. Notice that
            // the number of active y's is always even.
            auto activeYsIt = activeYs.begin();
            auto yUpperIt = yToReCheck.begin();
            while (activeYsIt != activeYs.end())
            {
                auto yLowerIt = std::lower_bound(yUpperIt, yToReCheck.end(), activeYsIt->first);
                ++activeYsIt;
                yUpperIt = std::upper_bound(yLowerIt, yToReCheck.end(), activeYsIt->first);
                ++activeYsIt;

                numPointsInside += std::distance(yLowerIt, yUpperIt);
            }


            //=================================================================
            // Points between two consecutive lines of vertical edges.
            //=================================================================
            // Get the points between the left/min and the right/max x-bounds.
            xBeginPointToCheckIt = xEndPointToCheckIt;
            xEndPointToCheckIt = std::lower_bound(xBeginPointToCheckIt, pointXs.end(), maxX);

            numPointsToCheck = std::distance(xBeginPointToCheckIt, xEndPointToCheckIt);
            yBeginPointToCheckIt = yEndPointToCheckIt;
            yEndPointToCheckIt = yBeginPointToCheckIt + numPointsToCheck;

            // Copy the y values of the test points whose x values are in
            // (minX, maxX), and sort them.
            yToCheck.resize(numPointsToCheck);
            std::copy(yBeginPointToCheckIt, yEndPointToCheckIt, yToCheck.begin());
            std::sort(yToCheck.begin(), yToCheck.end());

            // Skip the points outside and count the points inside. Notice that
            // the number of active y's is always even.
            activeYsIt = activeYs.begin();
            yUpperIt = yToCheck.begin();
            while (activeYsIt != activeYs.end())
            {
                auto yLowerIt = std::lower_bound(yUpperIt, yToCheck.end(), activeYsIt->first);
                ++activeYsIt;
                auto yUpperIt = std::upper_bound(yLowerIt, yToCheck.end(), activeYsIt->first);
                ++activeYsIt;
                numPointsInside += std::distance(yLowerIt, yUpperIt);
            }


            //=================================================================
            // Points on a line of a vertical edge, checked from the left.
            //=================================================================
            // Get the points at the right/max x-bound.
            xBeginPointToCheckIt = xEndPointToCheckIt;
            xEndPointToCheckIt = std::upper_bound(xBeginPointToCheckIt, pointXs.end(), maxX);

            numPointsToCheck = std::distance(xBeginPointToCheckIt, xEndPointToCheckIt);
            yBeginPointToCheckIt = yEndPointToCheckIt;
            yEndPointToCheckIt = yBeginPointToCheckIt + numPointsToCheck;

            // Copy the y values of the test points whose x values are equal to
            // maxX, and sort them.
            yToCheck.resize(numPointsToCheck);
            std::copy(yBeginPointToCheckIt, yEndPointToCheckIt, yToCheck.begin());
            std::sort(yToCheck.begin(), yToCheck.end());

            // Skip the points outside and count the points inside. Notice that
            // the number of active y's is always even.
            yToReCheck.resize(numPointsToCheck);

            activeYsIt = activeYs.begin();
            yUpperIt = yToCheck.begin();
            auto yToReCheckIt = yToReCheck.begin();
            while (activeYsIt != activeYs.end())
            {
                auto yLowerIt = std::lower_bound(yUpperIt, yToCheck.end(), activeYsIt->first);
                ++activeYsIt;

                // Copy the y values of the test points whose x values are
                // equal to maxX, but the y values need to be checked again.
                // They are already sorted.
                yToReCheckIt = std::copy(yUpperIt, yLowerIt, yToReCheckIt);

                yUpperIt = std::upper_bound(yLowerIt, yToCheck.end(), activeYsIt->first);
                ++activeYsIt;

                numPointsInside += std::distance(yLowerIt, yUpperIt);
            }
            // Copy the y values of the points that appeared to be outside for
            // being above the highest polygon point at this cross-section.
            yToReCheckIt = std::copy(yUpperIt, yToCheck.end(), yToReCheckIt);
            // Trim off any of the preallocated memory that remained unused.
            yToReCheck.resize(std::distance(yToReCheck.begin(), yToReCheckIt));

        }
        answers.push_back(numPointsInside);
        outStream << numPointsInside << std::endl;
    }

#ifdef USE_FILE
    for (int i = 0; i < numQueries; ++i)
    {
        long long int ans;
        inOutFile >> ans;
        if (ans != answers[i])
            outStream << "case: " << i + 1 << "  we: " << answers[i] << "  they: " << ans << std::endl;
    }
#endif

    return 0;
}
