#include <bits/stdc++.h>
using namespace std;

class City
{
public:
    int id;
    double x, y;

    City(int id, double x, double y)
    {
        this->id = id;
        this->x = x;
        this->y = y;
    }
};

class TSP
{
    vector<City> cities;
    vector<int> tour;
    int numCities;

public:
    TSP(vector<City> &cityList)
    {
        cities = cityList;
        numCities = cities.size();
        tour.resize(numCities);
    }

    double calculateDistance(City a, City b)
    {
        return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
    }

    double calculateTourDistance(const vector<int> &tour)
    {
        double totalDistance = 0.0;
        for (int i = 0; i < numCities - 1; i++)
        {
            totalDistance += calculateDistance(cities[tour[i]], cities[tour[i + 1]]);
        }
        totalDistance += calculateDistance(cities[tour[numCities - 1]], cities[tour[0]]);
        return totalDistance;
    }

    void printTour(const vector<int> &tour)
    {
        for (int city : tour)
        {
            cout << city << " -> ";
        }
        cout << tour[0] << endl;
    }

    void nearestNeighbour()
    {
        vector<bool> visited(numCities, false);
        tour.clear();
        tour.push_back(0);
        visited[0] = true;

        for (int i = 1; i < numCities; i++)
        {
            int lastCity = tour.back();
            int nearest = -1;
            double nearestDist = numeric_limits<double>::max();

            for (int j = 0; j < numCities; j++)
            {
                if (!visited[j])
                {
                    double dist = calculateDistance(cities[lastCity], cities[j]);
                    if (dist < nearestDist)
                    {
                        nearestDist = dist;
                        nearest = j;
                    }
                }
            }

            tour.push_back(nearest);
            visited[nearest] = true;
        }
    }

    void cheapestInsertion()
    {
        int n = cities.size();
        vector<int> tempTour;
        vector<bool> inTour(n, false);

        if (n < 3)
        {
            for (int i = 0; i < n; i++)
            {
                tempTour.push_back(i);
            }
            tour = tempTour;
            return;
        }

        tempTour.push_back(0);
        tempTour.push_back(1);
        tempTour.push_back(2);
        inTour[0] = inTour[1] = inTour[2] = true;

        while (tempTour.size() < n)
        {
            int bestCity = -1;
            int bestPosition = -1;
            double minCost = numeric_limits<double>::max();

            for (int i = 0; i < n; i++)
            {
                if (!inTour[i])
                {
                    for (int j = 0; j < tempTour.size(); j++)
                    {
                        int next = (j + 1) % tempTour.size();
                        double cost = calculateDistance(cities[tempTour[j]], cities[i]) +
                                      calculateDistance(cities[i], cities[tempTour[next]]) -
                                      calculateDistance(cities[tempTour[j]], cities[tempTour[next]]);

                        if (cost < minCost)
                        {
                            minCost = cost;
                            bestCity = i;
                            bestPosition = next;
                        }
                    }
                }
            }

            tempTour.insert(tempTour.begin() + bestPosition, bestCity);
            inTour[bestCity] = true;
        }

        tour = tempTour;
    }

    void randomInsertion()
    {
        vector<int> unvisitedCities;
        for (int i = 0; i < numCities; i++)
        {
            unvisitedCities.push_back(i);
        }

        // Start with a tour of two random cities
        tour.clear();
        int firstCity = unvisitedCities[rand() % unvisitedCities.size()];
        tour.push_back(firstCity);
        unvisitedCities.erase(find(unvisitedCities.begin(), unvisitedCities.end(), firstCity));

        int secondCity = unvisitedCities[rand() % unvisitedCities.size()];
        tour.push_back(secondCity);
        unvisitedCities.erase(find(unvisitedCities.begin(), unvisitedCities.end(), secondCity));

        // Close the tour by returning to the first city
        tour.push_back(firstCity);

        // Randomly insert remaining cities
        while (!unvisitedCities.empty())
        {
            int insertCity = unvisitedCities[rand() % unvisitedCities.size()];
            int bestPosition = -1;
            double minIncrease = numeric_limits<double>::max();

            for (size_t i = 0; i < tour.size() - 1; i++)
            {
                double increase = calculateDistance(cities[tour[i]], cities[insertCity]) +
                                  calculateDistance(cities[insertCity], cities[tour[i + 1]]) -
                                  calculateDistance(cities[tour[i]], cities[tour[i + 1]]);

                if (increase < minIncrease)
                {
                    minIncrease = increase;
                    bestPosition = i + 1;
                }
            }

            tour.insert(tour.begin() + bestPosition, insertCity);
            unvisitedCities.erase(find(unvisitedCities.begin(), unvisitedCities.end(), insertCity));
        }

        // Remove the duplicated first city at the end
        tour.pop_back();
    }

    void twoOpt()
    {
        bool improvement = true;

        while (improvement)
        {
            improvement = false;

            for (int i = 1; i < numCities - 1; i++)
            {
                for (int j = i + 1; j < numCities; j++)
                {
                    vector<int> newTour = tour;
                    reverse(newTour.begin() + i, newTour.begin() + j + 1);

                    double oldDistance = calculateTourDistance(tour);
                    double newDistance = calculateTourDistance(newTour);

                    if (newDistance < oldDistance)
                    {
                        tour = newTour;
                        improvement = true;
                    }
                }
            }
        }
    }

    void nodeShift()
    {
        bool improvement = true;

        while (improvement)
        {
            improvement = false;

            for (int i = 1; i < numCities; i++)
            {
                for (int j = 0; j < numCities; j++)
                {
                    if (i != j)
                    {
                        vector<int> newTour = tour;

                        int city = newTour[i];
                        newTour.erase(newTour.begin() + i);
                        newTour.insert(newTour.begin() + j, city);

                        double oldDistance = calculateTourDistance(tour);
                        double newDistance = calculateTourDistance(newTour);

                        if (newDistance < oldDistance)
                        {
                            tour = newTour;
                            improvement = true;
                        }
                    }
                }
            }
        }
    }

    void nodeSwap()
    {
        bool improvement = true;

        while (improvement)
        {
            improvement = false;

            for (int i = 1; i < numCities - 1; i++)
            {
                for (int j = i + 1; j < numCities; j++)
                {
                    vector<int> newTour = tour;

                    swap(newTour[i], newTour[j]);

                    double oldDistance = calculateTourDistance(tour);
                    double newDistance = calculateTourDistance(newTour);

                    if (newDistance < oldDistance)
                    {
                        tour = newTour;
                        improvement = true;
                    }
                }
            }
        }
    }

    vector<int> getTour()
    {
        return tour;
    }

    void setTour(const vector<int> &newTour)
    {
        tour = newTour;
    }

    double getTourDistance()
    {
        return calculateTourDistance(tour);
    }

    void runConstructiveAlgorithm(const string &algorithm)
    {
        tour.clear();
        tour.resize(numCities);

        if (algorithm == "NNH")
            nearestNeighbour();
        else if (algorithm == "Cheapest Insertion")
            cheapestInsertion();
        else if (algorithm == "Random Insertion")
            randomInsertion();
    }

    void runPerturbativeAlgorithm(const string &algorithm)
    {
        if (algorithm == "Two-Opt")
            twoOpt();
        else if (algorithm == "Node Shift")
            nodeShift();
        else if (algorithm == "Node Swap")
            nodeSwap();
    }
};

vector<City> readTSPFile(const string &filename)
{
    ifstream file(filename);
    vector<City> nodes;

    if (!file.is_open())
    {
        cerr << "Failed to open file: " << filename << endl;
        return nodes;
    }

    string line;
    bool reading_nodes = false;

    while (getline(file, line))
    {
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line == "NODE_COORD_SECTION")
        {
            reading_nodes = true;
            continue;
        }
        else if (line == "EOF" || line.empty())
        {
            break;
        }

        if (reading_nodes)
        {
            int id;
            double x, y;
            istringstream iss(line);
            if (iss >> id >> x >> y)
            {
                nodes.emplace_back(id, x, y);
            }
            else
            {
                cerr << "Error parsing line: " << line << endl;
            }
        }
    }

    file.close();
    return nodes;
}

#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(NULL));

    vector<string> filenames = {
        "a280.tsp", "berlin52.tsp", "bier127.tsp", "ch130.tsp", "ch150.tsp",
        "eil51.tsp", "eil76.tsp", "eil101.tsp", "kroA100.tsp", "kroB100.tsp",
        "kroC100.tsp", "kroD100.tsp", "kroE100.tsp", "lin105.tsp", "lin318.tsp",
        "pr76.tsp", "pr124.tsp", "pr144.tsp", "rat99.tsp", "rat195.tsp", "st70.tsp"};

    vector<string> constructiveAlgorithms = {
        "NNH", "Cheapest Insertion", "Random Insertion"};

    vector<string> perturbativeAlgorithms = {
        "Two-Opt", "Node Shift", "Node Swap"};

    // Open CSV file for output
    ofstream outFile("tsp_results.csv");
    if (!outFile.is_open())
    {
        cerr << "Failed to open output CSV file." << endl;
        return 1;
    }

    // Write CSV header
    outFile << "File,Constructive Algorithm,Initial Distance,Perturbative Algorithm,Final Distance,Improvement\n";

    for (const auto &file : filenames)
    {
        vector<City> nodes = readTSPFile(file);
        if (nodes.empty())
        {
            outFile << file << ",Failed to read file,,,,\n";
            continue;
        }

        TSP tsp(nodes);

        for (const auto &constructiveAlgo : constructiveAlgorithms)
        {
            // Run constructive algorithm
            tsp.runConstructiveAlgorithm(constructiveAlgo);
            vector<int> initialTour = tsp.getTour();
            double initialDistance = tsp.getTourDistance();

            // For each perturbative algorithm, use the initial tour
            for (const auto &perturbativeAlgo : perturbativeAlgorithms)
            {
                tsp.setTour(initialTour); // Reset to initial tour
                tsp.runPerturbativeAlgorithm(perturbativeAlgo);
                double finalDistance = tsp.getTourDistance();
                double improvement = initialDistance - finalDistance;

                // Write results to CSV
                outFile << file << "," << constructiveAlgo << "," <<initialDistance  << ","
                        <<perturbativeAlgo  << "," << finalDistance << "," << improvement << "\n";
            }
        }
    }

    outFile.close();
    cout << "Results written to tsp_results.csv" << endl;

    return 0;
}
