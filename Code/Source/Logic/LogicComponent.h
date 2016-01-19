#ifndef __LOGIC_COMPONENT_H
#define __LOGIC_COMPONENT_H

namespace WE
{
    //this class is meant to handle logic for classes
    //it is updated by the logic system
    //classes must implement the update method
    class LogicComponent
    {
    public:
        LogicComponent();

        virtual ~LogicComponent();

        //update the component
        virtual void Update(double delta) = 0;

        //set if the logic component is enabled
        void SetEnabled(bool enabled);

        //check if the logic component is enabled
        bool IsEnabled();
    private:
        bool m_Enabled;

    };
}


#endif //__LOGIC_COMPONENT_H