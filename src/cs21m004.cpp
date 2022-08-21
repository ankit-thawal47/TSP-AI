#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<queue>
#include<unordered_set>
using namespace std;

vector<unordered_map<int,double>> listOfDistances;
int populationSize = 50;
long long numOfCities;
priority_queue<pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > tourDistances;
vector<vector<int>> population; //
vector<vector<int> > parent1;
vector<vector<int> > parent2;


class City
{

    public:

    double x,y;

    City(double x, double y)
    {
        this->x = x;
        this->y = y;
    }


};

void generateInitialPopulation()
{
    //population size?
    //I'll be using path representaions

    //cout<<"Inside Initial Popl function"<<endl;

    for(int i=0;i<populationSize;i++)
    {
        //till i dont get those many individuals keep looping
        //how to store paths? ----> in NxN vector
        unordered_set<int> pathtracker; //this set is just to check if path is already present or not.

        vector<int> path;
        path.clear();
        int cityCount = 0;

        while(cityCount<numOfCities)
        {
            //cout<<"citycount :"<<cityCount<<" \t";
            int randomNum = rand()%numOfCities;

                while (pathtracker.find(randomNum) != pathtracker.end())
                {
                    //till I dont get new city number I will continue looping and generating random number
                    randomNum = (rand()%numOfCities);
                }
            //cout<<"random num :"<<randomNum<<endl;

            path.push_back(randomNum);
            pathtracker.insert(randomNum);

        cityCount++;
        }
        population.push_back(path);//add the path into population

       

        
      


    }

    //cout<<"Size of initial population "<<population.size()<<endl;

    for(int m=0;m<populationSize;m++)
        {
            population[m].push_back(population[m][0]);//as salesman has to return the city from which he started
        }

     for(int x=0;x<population.size();x++)
        {
            for(int y=0;y<population[0].size();y++)
                //cout<<population[x][y]<<"\t";

            cout<<endl;    
        }
        cout<<endl;    
}


void generateRandomTours()
{
    //store it in a minheap

    priority_queue<pair<double,int>,vector<pair<double,int>>,greater<pair<double,int>>> minHeaptours;
    // here double -> tour length AND int - number of entry in population vector


    for(int i=0;i<populationSize;i++)
    {
        double sum = 0;
        for(int j =1;j<=numOfCities;j++)
        {
           
            int citynum = population[i][j];
            //cout<<"citynum "<<citynum<<endl;
            sum += listOfDistances[population[i][j-1]].find(citynum)->second;
        }
        //cout<<"sum: "<<sum<<endl;
        minHeaptours.push(make_pair(sum,i));

    }

    tourDistances = minHeaptours;
}

void chooseParents()
{
    vector<vector<int> > random;
	vector<pair<double, int> > temp;
	int count = 0;
	parent1.clear(); parent2.clear();
	
    int noOfRandomGuesses = 4;

	while(count < noOfRandomGuesses)
	{
		temp.push_back(tourDistances.top());
		tourDistances.pop();
		count++;
	}
	//cout << tour_distances.size() << endl;
	for(int i = 0; i < noOfRandomGuesses; i++)
	{
		
		tourDistances.push(temp[i]);
		
	}
	//cout << tour_distances.size() << endl;
	for(int i = 0; i < noOfRandomGuesses; i++)
	{
		for(int j = 0; j < (noOfRandomGuesses - i); j++)
		{
			random.push_back(population[temp[i].second]);
		}
	}
	
	for(int i = 0; i < 5; i++)
	{
		parent1.push_back(random[rand() % random.size()]);
		parent2.push_back(random[rand() % random.size()]);
	}
}

void PMXcrossover()
{
    
}


int main()
{

    //INPUT FORMAT
    // First line - euclidean or non euclidean
    // Second line - no of cities N
    // 2D cordinates of cities
    // N X N matrix with dist from one node to another
    // cordinates and distance will be floating points (double)

    string distaceType;
    bool distType = false;
    
    getline(cin,distaceType);
    
    if(distaceType == "euclidean")
    {
        //cout<<"Given dist is euclidean"<<endl;
        distType = true;
    }
    else
    {
       // cout<<"dist is NOT euclidean";
    }

    cin>>numOfCities;
   // City cities[numberOfCities];
    vector<City> cities;

    for(long long i=0;i<numOfCities;i++)
    {
        
        double x,y;
        cin>>x>>y;

        City city(x,y);
        cities.push_back(city);
    }

    //accepting NXN matrix 
    //listOfDistances is vector NXN size
    //distance from 1 to all other N-1 node are mapped
    for(long long i=0;i<numOfCities;i++)
    {
        unordered_map<int,double> temp;
        for(long long j=0;j<numOfCities;j++)
        {
        double d;
        cin>>d;
        temp.insert(make_pair(j,d));
        }
        listOfDistances.push_back(temp);
    }

    /*cout<<"Generating COST Matrix 1"<<endl;
    for(int i=0;i<numOfCities;i++)
    {
        for(int j=0;j<numOfCities;j++)
        {
            cout<<listOfDistances[i][j]<<"\t";
        }

        cout<<"\n";
    }
    */


    //STEPS of GA
    //1. Initiliase population using some random function
    generateInitialPopulation();
    //2.
    //cout<<"Pointer on line 192"<<endl;
    generateRandomTours();


    /*
    cout<<"Generating COST Matrix 2"<<endl;
    for(int i=0;i<numOfCities;i++)
    {
        for(int j=0;j<numOfCities;j++)
        {
            cout<<listOfDistances[i][j];
        }

        cout<<"\n";
    }
    */


        //tourDistances.pop();//DELETE THIS LATER

    

    while(1)
    {
        chooseParents();

        PMXcrossover();

        for(int i = 0; i < numOfCities; i++)
        {
            //cout<<"printing best tour:"<<endl;
            cout<<population[tourDistances.top().second][i] << " ";
        }
        cout<<endl;
    }


}