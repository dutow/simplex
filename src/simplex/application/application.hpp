
#pragma once

namespace simplex {

/// <summary>	Minimal class representing an applicaiton. </summary>
class application {
   public:
    /// <summary>	Initializes the application. </summary>
    application(){};

    /// <summary>	Destructor. </summary>
    virtual ~application(){};

    /// <summary>	Runs the main loop of the application. </summary>
    virtual void run() = 0;
};
}