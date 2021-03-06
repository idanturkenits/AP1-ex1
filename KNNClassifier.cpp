#include "KNNClassifier.h"

#include <iostream>
KNNClassifier::KNNClassifier(std::vector<std::shared_ptr<Classified>>& classifiedObjects, int k)
{
    m_data = classifiedObjects;
    m_k = k;
}

void KNNClassifier::setK(const int k){
    m_k = k;
}

std::string KNNClassifier::predict(const Classified &cls)
{
    Algorithm<Classified> algo;

    algo.sortByDiffrence(m_data, cls);
    std::vector<std::shared_ptr<Classified>> knnFlowers = algo.getKSmallest(m_data, m_k);

    int result[]{0, 0, 0};
    for (int i = 0; i < m_k; i++)
    {
        if (knnFlowers[i]->getLabel().compare("Iris-setosa") == 0)
        {
            result[0]++;
        }
        else if (knnFlowers[i]->getLabel().compare("Iris-virginica") == 0)
        {
            result[1]++;
        }
        else if (knnFlowers[i]->getLabel().compare("Iris-versicolor") == 0)
        {
            result[2]++;
        }
    }

    int max = result[0] > (result[1] > result[2] ? result[1] : result[2]) ? result[0] : (result[1] > result[2] ? result[1] : result[2]);

    if (result[0] == max)
        return "Iris-setosa";
    if (result[1] == max)
        return "Iris-virginica";
    return "Iris-versicolor";
}