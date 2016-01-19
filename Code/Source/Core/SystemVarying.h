#ifndef __SYSTEM_VARYING_H
#define __SYSTEM_VARYING_H

#include "SystemCallback.h"
#include "Entity.h"

#include <cassert>
#include <typeinfo>
#include <vector>

namespace WE
{

    /*
    The system varying will be handled by the system to hold any type of system
    any system passed to it must implement the following functions:

    std::vector<SystemCallback*> GetCallbacks();
    */
    class SystemVarying
    {
    public:
        //this will pass a system to the system varying
        template<typename System>
        SystemVarying(System* sys);

        //move constructor
        SystemVarying(SystemVarying&& system);

        //cant copy
        SystemVarying(const SystemVarying& system) = delete;

        //this will delete the system pointer
        virtual ~SystemVarying();

        //this will return all the callbacks associated to the system
        std::vector<SystemCallback*> GetCallbacks();

        //check if a type matches of not
        template<typename type>
        bool Match();

        //returns the system associated to the varying
        template<typename system>
        system* GetSystem();

    private:
        //This is the interface class for the varying, it will define the necessary interface
        struct Varying
        {
            //empty virtual destructor
            virtual ~Varying() {};


            //get callbacks will return all the callbacks to be called at iterations
            virtual std::vector<SystemCallback*> GetCallbacks() = 0;

            //this will check if the type matches
            virtual void Match() = 0;
        };

        //this is the main class within the system varying, it handles all the system types
        template<typename Type>
        class DerivedVarying : public Varying
        {
        public:
            //create a derived varying that takes the system
            DerivedVarying(Type* t);
            //destroy the system
            virtual ~DerivedVarying();

            //this will return the callback of the system
            std::vector<SystemCallback*> GetCallbacks();

            //check against the type
            void Match();

            //this will return the system associated to the varying
            Type* GetSystem();

        private:
            //this holds the pointer to the type
            Type* m_Inner;
        };

        //this will hold the system varying
        Varying* m_PlaceHolder;
    };


    template<typename System>
    SystemVarying::SystemVarying(System* sys)
    {
        //make sure the system being passed isnt nullptr
        assert(sys != nullptr);
        m_PlaceHolder = New DerivedVarying<System>(sys);
    }



    template<typename Type>
    SystemVarying::DerivedVarying<Type>::DerivedVarying(Type* t)
    {
        m_Inner = t;
    }

    template<typename Type>
    SystemVarying::DerivedVarying<Type>::~DerivedVarying()
    {
        //delete the inner system
        if (m_Inner != nullptr)
        {
            SafeDelete(m_Inner);
            m_Inner = nullptr;
        }
    }

    template<typename Type>
    std::vector<SystemCallback*>  SystemVarying::DerivedVarying<Type>::GetCallbacks()
    {
        //return the callbacks of the system
        return m_Inner->GetCallbacks();
    }

    template<typename type>
    bool SystemVarying::Match()
    {
		//use the try catch infrastructure to throw the object held in
		try
		{
			m_PlaceHolder->Match();
		}
		//catch the object and if it is polymorphic itll return true
		catch (type* t)
		{
			return true;
		}
		catch (...)
		{
			return false;
		}
    }

    template<typename Type>
    void SystemVarying::DerivedVarying<Type>::Match()
    {

		throw m_Inner;
    }

    template<typename Type>
    Type* SystemVarying::DerivedVarying<Type>::GetSystem()
    {
        return m_Inner;
    }

    //returns the system associated to the varying
    template<typename system>
    system* SystemVarying::GetSystem()
    {
        //casts the place holder and returns the system
        //no type checking is done, user should check before retrieving
        return dynamic_cast<DerivedVarying<system>*>(m_PlaceHolder)->GetSystem();
    }


}

#endif