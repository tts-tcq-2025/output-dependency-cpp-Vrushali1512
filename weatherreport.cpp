#include <iostream>
#include <string>
#include <assert.h>

namespace WeatherSpace
{
    // Existing interface
    class IWeatherSensor {
        public:
            virtual double TemperatureInC() const = 0;
            virtual int Precipitation() const = 0;
            virtual int Humidity() const = 0;
            virtual int WindSpeedKMPH() const = 0;
            virtual ~IWeatherSensor() = default;
    };

    // Base stub to inherit from
    class SensorStubBase : public IWeatherSensor {
        double temp;
        int precip;
        int humidity;
        int windSpeed;

    public:
        SensorStubBase(double t, int p, int h, int w)
            : temp(t), precip(p), humidity(h), windSpeed(w) {}

        double TemperatureInC() const override { return temp; }
        int Precipitation() const override { return precip; }
        int Humidity() const override { return humidity; }
        int WindSpeedKMPH() const override { return windSpeed; }
    };

    // Multiple stubs with different data to exercise all branches
    class SunnyStub : public SensorStubBase {
    public:
        SunnyStub() : SensorStubBase(30, 10, 50, 10) {}
    };

    class PartlyCloudyStub : public SensorStubBase {
    public:
        PartlyCloudyStub() : SensorStubBase(30, 30, 60, 10) {}
    };

    class StormyStub : public SensorStubBase {
    public:
        StormyStub() : SensorStubBase(30, 70, 80, 60) {}
    };

    // The Report function remains the same for now
    string Report(const IWeatherSensor& sensor)
    {
        int precipitation = sensor.Precipitation();
        string report = "Sunny Day";

        if (sensor.TemperatureInC() > 25)
        {
            if (precipitation >= 20 && precipitation < 60)
                report = "Partly Cloudy";
            else if (sensor.WindSpeedKMPH() > 50)
                report = "Alert, Stormy with heavy rain";
        }
        return report;
    }

    void TestSunny()
    {
        SunnyStub sensor;
        string report = Report(sensor);
        cout << report << endl;
        // Test expects Sunny Day exactly
        assert(report == "Sunny Day");
    }

    void TestPartlyCloudy()
    {
        PartlyCloudyStub sensor;
        string report = Report(sensor);
        cout << report << endl;
        // Test expects Partly Cloudy exactly
        assert(report == "Partly Cloudy");
    }

    void TestStormy()
    {
        StormyStub sensor;
        string report = Report(sensor);
        cout << report << endl;
        // Test expects Alert, Stormy with heavy rain exactly
        assert(report == "Alert, Stormy with heavy rain");
    }
}
