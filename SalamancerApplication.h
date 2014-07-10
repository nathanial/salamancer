#ifndef __SalamancerApplication_h_
#define __SalamancerApplication_h_

#include "BaseApplication.h"

class SalamancerApplication : public BaseApplication
{
public:
    SalamancerApplication(void);
    virtual ~SalamancerApplication(void);

protected:
    virtual void createScene(void);
};

#endif // #ifndef __TutorialApplication_h_
