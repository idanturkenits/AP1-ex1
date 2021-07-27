#include <iostream>
#include "KNNClassifier.h"
#include <math.h>
#include <algorithm>

KNNClassifier::KNNClassifier(std::vector<Flower> flowerArray)
{
    data = flowerArray;
}

std::vector<Flower> KNNClassifier::findKNN(const int k, const Flower &flower)
{
    // Sotring the array
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data.size() - 1; j++)
        {
            if (data[j].getDistance(flower) > data[j + 1].getDistance(flower))
            {
                Flower temp(data[j]);
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }

    std::vector<Flower> flowers;
    for (int i = 0; i < k; i++)
    {
        flowers.push_back(data[i]);
    }
    return flowers;
}

std::string KNNClassifier::predict(const Flower &flower)
{
    int k = 5;
    std::vector<Flower> knnFlowers = findKNN(k, flower);
    int result [] {0,0,0};
    for (int i = 0; i < k; i++)
    {
        if(knnFlowers[i].getLabel().compare("setosa") == 0){result [0]++;}
        if(knnFlowers[i].getLabel().compare("virginica") == 0){result [1]++;}
        if(knnFlowers[i].getLabel().compare("versicolor") == 0){result [2]++;}        
    }

    int max = result[0] > ( result[1] > result[2] ? result[1] : result[2]) ? result[0] : ( result[1] > result[2] ? result[1] : result[2]);

    if(result[0] == max)
        return "setosa";
    if(result[1] == max)
        return "virginica";
    return "versicolor";

}