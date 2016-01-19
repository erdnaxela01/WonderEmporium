#ifndef __COMPONENT_H
#define __COMPONENT_H

namespace WE
{
    class Entity;

    //this is the core class of the system,
    //it is a container class that permits the entity from holding any kind of object
    class Component
    {
    public:
        //this will set the component for the system
        template<typename Type>
        Component(Type* type);

        //destroy the vaying
        virtual ~Component();

        //cant copy the component
        Component(const Component& c) = delete;

        //can only move it
        Component(Component&& c);

        //match the type of the component
        template<typename Type>
        bool Match();

        //return the component associated
        template<typename component>
        component* GetComponent();

        //return the address of the component
        void* GetAddress();


    private:

        //interface class for the values
        struct Varying
        {
            virtual ~Varying() {};

            //check if the type matches
            virtual void Match() = 0;

            virtual void* GetAddress() = 0;
        };

        template<typename Type>
        class DerivedVarying : public Varying
        {
        public:
            //sets the component associated with the varying
            DerivedVarying(Type* t);


            virtual ~DerivedVarying() {};


            //check the type
            void Match();

            //return the component
            Type* GetComponent();

            //get the address
            void* GetAddress();
        private:
            Type* m_Inner;
        };

        Varying* m_PlaceHolder;
    };


    //this will set the component for the system
    template<typename Type>
    Component::Component(Type* type)
    {
        m_PlaceHolder = New DerivedVarying<Type>(type);
    }

    //match the type of the component
    template<typename Type>
    bool Component::Match()
    {
		//use the try catch infrastructure in order to return an unknown type
		try
		{
			m_PlaceHolder->Match();
		}
		//if the type is polymorphic itll fit this catch which means it can return true
        //ignore the warning, its not unused
		catch (Type* t)
		{
			return true;
		}
        catch (...)
        {
            return false;
        }
        return false;
    }

    //return the component associated
    template<typename component>
    component* Component::GetComponent()
    {
        return reinterpret_cast<component*>(m_PlaceHolder->GetAddress());
    }

    template<typename Type>
    Component::DerivedVarying<Type>::DerivedVarying(Type* t)
    {
        m_Inner = t;
    }




    //check the type
    template<typename Type>
    void Component::DerivedVarying<Type>::Match()
    {
		//throw inner in order to represent the type
		throw m_Inner;
    }


    //return the component
    template<typename Type>
    Type* Component::DerivedVarying<Type>::GetComponent()
    {
        return m_Inner;
    }

    template<typename Type>
    void* Component::DerivedVarying<Type>::GetAddress()
    {
        return m_Inner;
    }


}
#endif