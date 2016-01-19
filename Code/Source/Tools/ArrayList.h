#ifndef __ARRAY_LIST_H
#define __ARRAY_LIST_H

#include <cassert>
#include "../Source/MyLibs/Memory/MemoryTracker.h"

const unsigned int ARRAY_LIST_DEFAULT_SIZE = 100;

//this class will hold things in arrays allocated to a specific size and allocates them in chunks
template<typename type, unsigned int blockSize = ARRAY_LIST_DEFAULT_SIZE>
class ArrayList
{
public:
    static const unsigned int ARRAY_LIST_BLOCK_SIZE = blockSize;

    //initializes the array to a size of 100
    ArrayList();

	ArrayList(ArrayList&) = delete;
	ArrayList(ArrayList&&) = delete;

	ArrayList& operator=(ArrayList&) = delete;
	ArrayList& operator=(ArrayList&&) = delete;

    //destroy all the objects
    virtual ~ArrayList();
    //return the size of the array
    unsigned int Size();
    //get the area of the area
    unsigned int Area();
    //push back an object within the array
    void PushBack(type&);
    //push back an object within the array
    void PushBack(type&&);
    //remove the last object within the array
    void PopBack();
    //get the last object
    type& Back();
    //get the first object
    type& Front();
    //get an object at this index
    type& At(unsigned int);
    //get an object at this index, no bound checking
    type& operator[](unsigned int);
private:
    unsigned int m_Size;
    unsigned int m_BlockCount;

    struct ArrayBlock
    {
        //construct an array block
        ArrayBlock();
        //destroy the array block
        void Destroy(unsigned int amount = blockSize);
        //the array for the types
        char Array[blockSize * sizeof(type)];
        //the previous block
        ArrayBlock* Previous;
        //the next block
        ArrayBlock* Next;
    private:

    };

    ArrayBlock* m_Start;
    ArrayBlock* m_CurrentLast;

};


template<typename type, unsigned int blockSize>
ArrayList<type, blockSize>::ArrayList() : m_BlockCount(1), m_Size(0)
{
    m_Start = New ArrayBlock;
    m_CurrentLast = m_Start;

}

template<typename type, unsigned int blockSize>
ArrayList<type, blockSize>::~ArrayList()
{
    //set the current block as the first
    ArrayBlock* currentBlock = m_Start;
    //run through all the blocks
    for (unsigned int i= 0; i < m_BlockCount; i++)
    {
        //set the next block and destroy the current block
        ArrayBlock* temp = currentBlock->Next;
        currentBlock->Destroy(m_Size % blockSize);
        SafeDelete(currentBlock);
        currentBlock = temp;
    }
}

template<typename type, unsigned int blockSize>
unsigned int ArrayList<type, blockSize>::Size()
{
    //get the size of the array
    return m_Size;
}

template<typename type, unsigned int blockSize>
unsigned int ArrayList<type, blockSize>::Area()
{
    //return the total size of the area
    return m_BlockCount * blockSize;
}

template<typename type, unsigned int blockSize>
void ArrayList<type, blockSize>::PushBack(type& t)
{
    //if the size mode the block size is 0 that means were at the end of our block
    if (m_Size % blockSize == 0)
    {
        //if the size is equal to the total size that means we need a new block
        if (m_Size == m_BlockCount * blockSize)
        {
            //create a new array block
            m_CurrentLast->Next = New ArrayBlock();
            m_CurrentLast->Next->Previous = m_CurrentLast;
            m_CurrentLast = m_CurrentLast->Next;
            //add the block to the block count
            ++m_BlockCount;
        }
        else
        {
            //set the current last block to be the next block
            m_CurrentLast = m_CurrentLast->Next;
        }
    }
    //cast the char to a type* and set the value
    *reinterpret_cast<type*>(&m_CurrentLast->Array[((m_Size % blockSize))* sizeof(type)]) = t;
    //add 1 to the size
    ++m_Size;
}

template<typename type, unsigned int blockSize>
void ArrayList<type, blockSize>::PushBack(type&& t)
{
    
    if (m_Size % blockSize == 0)
    {
        if (m_Size == m_BlockCount * blockSize)
        {
            m_CurrentLast->Next = New ArrayBlock();
            m_CurrentLast->Next->Previous = m_CurrentLast;
            m_CurrentLast = m_CurrentLast->Next;
            ++m_BlockCount;
        }
        else
        {
            m_CurrentLast = m_CurrentLast->Next;
        }
    }
    *reinterpret_cast<type*>(&m_CurrentLast->Array[((m_Size % blockSize))* sizeof(type)]) = t;
    ++m_Size;
}

template<typename type, unsigned int blockSize>
void ArrayList<type, blockSize>::PopBack()
{
    //if the size is 0 crash
    assert(m_Size != 0);
    
    ArrayBlock* temp = m_CurrentLast;
    //if the block is about to end set the temp as that block
    if (m_Size % blockSize == 1)
    {
        temp = m_CurrentLast->Previous;
    }
    //destroy the type and decrement the size
    reinterpret_cast<type*>(&m_CurrentLast->Array[(((m_Size - 1) % blockSize)) * sizeof(type)])->type::~type();
    --m_Size;
    //set the current area block
    m_CurrentLast = temp;
    
}

template<typename type, unsigned int blockSize>
type& ArrayList<type, blockSize>::Back()
{
    //make sure the size isnt 0
    assert(m_Size != 0);
    //get the last value
    return *reinterpret_cast<type*>(&m_CurrentLast->Array[(((m_Size - 1) % blockSize))* sizeof(type)]);
}

template<typename type, unsigned int blockSize>
type& ArrayList<type, blockSize>::Front()
{

    //make sure the size isnt 0
    assert(m_Size != 0);
    //return the first value
    return *reinterpret_cast<type*>(&m_Start->Array[0]);
}

template<typename type, unsigned int blockSize>
type& ArrayList<type, blockSize>::At(unsigned int index)
{
    //if the index is over the size
    if(index > m_Size)
    {
        throw std::logic_error("Out of bounds of the array");
    }

    //get the block for the index
    unsigned int block = std::floor(index / (blockSize));

    ArrayBlock* temp = m_Start;
    //loop to that block
    for (unsigned int i = 0; i < block; i++)
    {
        temp = temp->Next;
    }
    //get the value
    return *reinterpret_cast<type*>(&temp->Array[(index % blockSize) * sizeof(type)]);

}

template<typename type, unsigned int blockSize>
type& ArrayList<type, blockSize>::operator[](unsigned int index)
{
    //get the block
    unsigned int block = static_cast<unsigned int>(std::floor(index / (blockSize)));

    ArrayBlock* temp = m_Start;
    //loop to the block
    for (unsigned int i = 0; i < block; i++)
    {
        temp = temp->Next;
    }
    //get the value
    return *reinterpret_cast<type*>(&temp->Array[(index % blockSize) * sizeof(type)]);
}

template<typename type, unsigned int blockSize>
ArrayList<type, blockSize>::ArrayBlock::ArrayBlock() : Previous(this), Next(this)
{

}

template<typename type, unsigned int blockSize>
void ArrayList<type, blockSize>::ArrayBlock::Destroy(unsigned int amount)
{
    //loop through all the values and destroy them
    for (unsigned int i = 0; i < amount; i++)
    {
        unsigned int index = i * sizeof(type);
        reinterpret_cast<type*>(Array[index])->type::~type();
    }
}


#endif //__ARRAY_LIST_H