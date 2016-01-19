#ifndef __SYSTEM_CALLBACK_H
#define __SYSTEM_CALLBACK_H

#include <functional>
namespace WE
{

    /*
    This will hold any function as a callback that takes no arguments and returns void
    */
    class SystemCallback
    {
    public:
        //create an alias for the callback
        using CallbackFunction = void(*)();

        //create a bound callback
        template<typename func, typename... args>
        SystemCallback(func, args...);

        //cant copy due to destructor
        SystemCallback(const SystemCallback& sys) = delete;
        //can only move which will replace the callback with nullptr
        SystemCallback(SystemCallback&& sys);

        //will destroy the Callback object
        virtual ~SystemCallback();

        //will execute the callback
        void Execute();

    private:
        //this is the interface class associated to the system callback
        struct Callback
        {
            //does nothing
            virtual ~Callback() {};
            //has to be overriden to execute the function
            virtual void Execute() = 0;
        };

        //this class will handle the bound functions or function objects
        template<typename bound>
        class DerivedCallback :public Callback
        {
        public:
            //this will take any object that takes no arguments
            DerivedCallback(bound);

            virtual ~DerivedCallback();

            //this will execute the callback
            void Execute();
        private:
            bound m_Function;
        };

        //this specialization will handle function pointers
        template<>
        class DerivedCallback<CallbackFunction> :public Callback
        {
        public:

            //this will execute the function pointer
            void Execute()
            {
                (*m_Function)();
            }
        private:
            CallbackFunction m_Function;
        };

        Callback* m_Callback;
    };


    template<typename func, typename... args>
    SystemCallback::SystemCallback(func function, args... arguments)
    {
        //create  a callback
        m_Callback = New DerivedCallback<decltype(std::bind(function, arguments...))>(std::bind(function, arguments...));
    }



    template<typename bound>
    SystemCallback::DerivedCallback<bound>::DerivedCallback(bound b) : m_Function(b)
    {
    }
    template<typename bound>
    SystemCallback::DerivedCallback<bound>::~DerivedCallback()
    {

    }
    template<typename bound>
    void SystemCallback::DerivedCallback<bound>::Execute()
    {
        //call the function object
        m_Function();
    }

}

#endif