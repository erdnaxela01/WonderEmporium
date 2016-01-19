#ifndef __INPUT_H
#define __INPUT_H

#include <typeinfo>

namespace WE
{
    /*
    This class will hold any type of data and return it when you call get,
    however, it will 
    */
    class Data
    {
    public:
        Data();

        //create the data
        template<typename data>
        void Create(data* d);

        Data(Data&) = delete;
        Data& operator=(Data&) = delete;
        Data(Data&&);
        Data& operator=(Data&&);

        //destroy the data
        virtual ~Data();

        //get the data
        template<typename type>
        type* Get();

        //check if it is a certain type
        template<typename type>
        bool IsType();

        struct PlaceHolder
        {
            virtual ~PlaceHolder();
            virtual void Get() = 0;
        };

        template<typename type>
        struct Holder : public PlaceHolder
        {
            virtual ~Holder();
            //will throw the data
            void Get();
            type* data;
        };

    private:
        PlaceHolder* m_PlaceHolder;
    };

    template<typename data>
    void Data::Create(data* d)
    {
        //set the data
        assert(d != nullptr);
        assert(m_PlaceHolder == nullptr);
        Holder < data >* holder = New Holder<data>();
        holder->data = d;
        m_PlaceHolder = holder;
    }

    template<typename type>
    type* Data::Get()
    {
        //try catch block in order to be able to get inheritence to work with this system
        try
        {
            m_PlaceHolder->Get();
        }
        catch (type* t)
        {
            return t;
        }
        catch (...)
        {
            return nullptr; 
        }
    }

    template<typename type>
    bool Data::IsType()
    {
        //try catch block in order to be able to get inheritence to work with this system
        try
        {
            m_PlaceHolder->Get();
        }
        catch (type* t)
        {
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    template<typename type>
    void Data::Holder<type>::Get()
    {
        //throw the data
        throw data;
    }

    template<typename type>
    Data::Holder<type>::~Holder()
    {
        //destroy the data
        if (data != nullptr)
        {
            SafeDelete(data);
            data = nullptr;
        }
    }
    


    struct Input
    {
        Input() :name("") {};
        std::string name;
        Data data;
    };
}

#endif //__INPUT_H