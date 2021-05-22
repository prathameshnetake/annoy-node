#include "iostream"
#include "annoylib.h"
#include "kissrandom.h"

int main()
{

    const int f = 40;
    double *vec = (double *)malloc(f * sizeof(double));

    AnnoyIndex<int, double, Angular, Kiss32Random, AnnoyIndexMultiThreadedBuildPolicy> t = AnnoyIndex<int, double, Angular, Kiss32Random, AnnoyIndexMultiThreadedBuildPolicy>(f);

    for (int temp = 0; temp < 1000; temp++)
    {

        for (int z = 0; z < f; ++z)
        {
            vec[z] = (rand() % 100);
        }
        t.add_item(temp, vec);
    }

    t.build(10);

    // t.save("test.ann");

    for (int z = 0; z < f; ++z)
    {
        vec[z] = (rand() % 100);
    }

    std::vector<int> result;
    std::vector<double> distance;

    t.get_nns_by_vector(vec, 10, 10, &result, &distance);

    for (int j = 0; j < 10; j++)
    {
        // double *v = (double *)malloc(f * sizeof(double));
        double *v = new double[f]();

        t.get_item(result[j], v);
        std::cout << result[j] << std::endl;
        std::cout << distance[j] << std::endl;
        for (int i = 0; i < f; i++)
        {
            std::cout << v[i] << " ";
        }
        std::cout << std::endl;
    }

    std::cout
        << "Hello World!" << std::endl;
    return 0;
}