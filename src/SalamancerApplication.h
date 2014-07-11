#ifndef __SalamancerApplication_h_
#define __SalamancerApplication_h_

#include "BaseApplication.h"
#include "framework/Volume.h"

class SalamancerApplication : public BaseApplication
{
public:
    SalamancerApplication(void);
    virtual ~SalamancerApplication(void);

protected:
    virtual void createScene(void);
    
private:
    Volume createVolume();
        
};

#endif // #ifndef __TutorialApplication_h_
