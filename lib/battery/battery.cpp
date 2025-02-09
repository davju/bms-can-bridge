#include "battery.h"
void Battery::setBMSType(BMS_IMPL_TYPES bms_type)
{
    bms = BMSFactory::createBMSImpl(bms_type);
}

std::shared_ptr<BMS> Battery::getBMS(void)
{
    return bms;
}

// determine the maximum battery current based on the current temperature and soc of the battery
int Battery::setMaxCurrent(float SOC, float temperature)
{
}

int Battery::findLowerIndex(const std::vector<double> &vec, double value)
{
    // Ensure the value is within the table bounds.
    assert(value >= vec.front() && value <= vec.back());

    for (int i; i < vec.size(); i++)
    {
        if (value >= vec[i] && value <= vec[i + 1])
        {
            return i;
        }
    }
    return vec.size() - 2; // Fallback; should not be reached if value is within bounds.
}

double Battery::bilinearInterpolate(double soc, double temp)
{
    // Ensure the input is within the bounds of the table.
    assert(soc >= soc_points.front() && soc <= soc_points.back());
    assert(temp >= temp_points.front() && temp <= temp_points.back());

    // Find the grid cell in which (soc, temp) lies.
    int i = findLowerIndex(soc_points, soc);
    int j = findLowerIndex(temp_points, temp);

    // Grid corner coordinates.
    double soc0 = soc_points[i];
    double soc1 = soc_points[i + 1];
    double temp0 = temp_points[j];
    double temp1 = temp_points[j + 1];

    // Values at the four corners.
    double q11 = discharge_current_table[i][j];
    double q21 = discharge_current_table[i + 1][j];
    double q12 = discharge_current_table[i][j + 1];
    double q22 = discharge_current_table[i + 1][j + 1];

    // Bilinear interpolation formula.
    double denom = (soc1 - soc0) * (temp1 - temp0);
    double interpolatedValue =
        (q11 * (soc1 - soc) * (temp1 - temp) +
         q21 * (soc - soc0) * (temp1 - temp) +
         q12 * (soc1 - soc) * (temp - temp0) +
         q22 * (soc - soc0) * (temp - temp0)) /
        denom;

    return interpolatedValue;
}
