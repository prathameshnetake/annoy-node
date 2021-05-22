#include <iostream>
#include <string.h>
#include "annoylib.h"
#include "kissrandom.h"

class AnnoyIndex
{

    std::string strPath;
    short iVecSize;
    AnnoyIndex<int, double, Angular, Kiss32Random, AnnoyIndexMultiThreadedBuildPolicy> objAnnoyIdx;

public:
    AnnoyIndex();
    AnnoyIndex(std::string p_strPath, short p_size)
    {
        strPath = p_strPath;
        iVecSize = p_size;

        objAnnoyIdx = AnnoyIndex<int, double, Angular, Kiss32Random, AnnoyIndexMultiThreadedBuildPolicy>(iVecSize);
    }

    void build()
    {
        for (int temp = 0; temp < 1000; temp++)
        {

            for (int z = 0; z < f; ++z)
            {
                vec[z] = (rand() % 100);
            }
            t.add_item(temp, vec);
        }

        t.build(10);
    }
};