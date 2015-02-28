
#pragma once

namespace simplex {

/// <summary>	Abstract drawable object. </summary>
class drawable {
   public:
    /// <summary>	Destructor. </summary>
    virtual ~drawable(){};

    /// <summary>	Renders this object. </summary>
    virtual void render() = 0;
};
}