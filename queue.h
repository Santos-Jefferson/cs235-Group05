/***********************************************************************
* Header:
*    Queue
* Summary:
*    This class contains the notion of a Queue: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the Queue, set, Queue, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Queue         : A class that holds stuff
*        QueueIterator : An interator through Queue
* Author
*    Makram Ibrahim
************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>
#include <iostream>
#include <queue>

/************************************************
 * CONTAINER
 * A class that holds stuff
 ***********************************************/
template <class T>
class Queue
{
public:
   // default constructor : empty and kinda useless
   Queue() : numElements(0), numCapacity(0), data(NULL), iHead(0), iTail(0) {}

   // non-default constructor : pre-allocate
   Queue(int numCapacity) throw (const char *);

   // copy constructor : copy it
   Queue(const Queue & rhs) throw (const char *);
   
   // destructor : free everything
   ~Queue()        { if (numCapacity) delete [] data; }

   /**********************************************************
   * Operator=: Assignment operator. This method takes a Queue as 
   * a parameter and copies all the elements to this. If the current 
   * buffer size is sufficient, not allocation is made. If the current
   * buffer size is not sufficient, enough space is allocated to accomodate 
   * the new data. If there is insufficient memory to allocate a new buffer, 
   * then the following exception is thrown:ERROR: Unable to allocate a 
   * new buffer for Queue. It also returns *this by-reference as all 
   * assignment operators should
   ***************************************************************/
    Queue<T>& operator=(const Queue<T> &rhs) throw (const char *)
   {
      if(rhs.numElements == 0)
      {
         numCapacity = numElements = 0;
         data = NULL;
      }
   
        numCapacity = rhs.numCapacity;
        numElements = rhs.numElements;
        iHead = rhs.iHead;
        iTail = rhs.iTail;

      try 
        {
           data = new T[numCapacity];
        }
      catch (std::bad_alloc) 
        {
            throw "ERROR: Unable to allocate a new buffer for Queue.";
        }
     

       for (int i = 0; i < numElements; i++) 
       {
         data[i] = rhs.data[i];
       }

      return *this;
   }
 
   /***************************************************
   * empty(): Test whether the Queue is empty.This method 
   * takes no parameters and returns a Boolean value.
   **************************************************/
   bool empty() const  { return numElements == 0;       }

  /****************************************************
  * size(): Return the Queue size. This method takes no 
  * parameters and returns an integer value.
  *******************************************************/
   int size() const    { return numElements;              }

  /****************************************************
  * capacity(): Return the number of elements that can be 
  * held in the currently allocated storage. This method
  *  takes no parameters and returns an integer value.
  *******************************************************/
   int capacity() const { return numCapacity;            }

  /*****************************************************
  * clear(): Clear the contents. This method takes no 
  * parameters and returns nothing. Note that you do not
  *  need to free the allocated memory; just set the size 
  * member variable to zero.
  *******************************************************/
   void clear()        { numElements = 0;                 }
 
  /******************************************************
  * push(): Adds an item to the container. This method takes 
  * a single parameter (the item to be added to the end of the 
  * Queue) and has no return value. Note that if the Queue is 
  * full, then the capacity will be doubled. In the case of an 
  * allocation error, the following c-string exception will be throw:
  * ERROR: Unable to allocate a new buffer for Queue
  *****************************************************************/
   void push(const T & t) throw (const char *);
  
  /*******************************************************
  * pop(): Removes an item from the end of the Queue, serving 
  * to reduce the size by one. Note that if the Queue is already 
  * empty, the following c-string exception will be thrown:
  * ERROR: Unable to pop from an empty Queue
  *********************************************************/
   void  pop() throw (const char *)
   {
       if (!empty())
       {
          iHead = (iHead + 1) % numCapacity;
          numElements--;
       }
       else 
         {
            throw "ERROR: attempting to pop from an empty queue";
         }
    }

   /***************************************************
   * top(): Returns the item currently at the end of the Queue. 
   * This item is returned by-reference so the last item can be 
   * changed through the top() method. If the Queue is currently
   * empty, the following exception will be thrown:
   * ERROR: Unable to reference the element from an empty Queue 
   ************************************************************/
   T & front() throw (const char *)
   {
      if (!empty()) 
      {
         return data[iHead];
      }
      else
      {
         throw "ERROR: attempting to access an item in an empty queue";
      }
   }

    /***************************************************
   * back(): Returns the item currently at the back of 
   * the queue. This item is returned by-reference so,
   * the last item can be changed through the back() method. 
   * If the queue is currently empty, the following exception
   * will be thrown:ERROR: attempting to access an item in an empty queue
   ************************************************************/
   T & back() throw (const char *)
   {
      if (!empty()) 
      {
         return data[iTail];
      }
      else
      {
         throw "ERROR: attempting to access an item in an empty queue";
      }
   }

private:
   T * data;             // dynamically allocated array of T
   int numElements;      // how many items are currently in the Queue?
   int numCapacity;      // how many items can I put on the Queue before full?
   int iTail;            // What index is the back of a queue
   int iHead;            // What index is the front of a queue
};

/*******************************************
 * Queue :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Queue <T> :: Queue(const Queue <T> & rhs) throw (const char *)
{
   assert(rhs.numCapacity >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.numCapacity == 0)
   {
      numCapacity = numElements = 0;
      iHead = iHead = 0;
      data = NULL;
      return;
   }

   // copy over the numCapacity and size
   assert(rhs.numElements >= 0 && rhs.numElements <= rhs.numCapacity);
   this->numCapacity = rhs.numCapacity;
   this->numElements = rhs.numElements;
   this->iHead = rhs.iHead;
   this->iTail = rhs.iTail;
   
      // attempt to allocate
  
    try
    {
       data = new T[numCapacity]; 
       for (int i = 0; i < numCapacity; i++)
          data[i] = rhs.data[i];         
    }

    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate buffer";
    }

   int front = iHead;

    for (int i = 0; i < numElements; i++)
    {
       data[front] = rhs.data[front];
       front = (front + 1) % numCapacity;
    } 
}

/**********************************************
 * Queue : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Queue to "numCapacity"
 **********************************************/
template <class T>
Queue <T> :: Queue(int numCapacity) throw (const char *)
{
   assert(numCapacity >= 0);
   
   // do nothing if there is nothing to do
   if (numCapacity == 0)
   {
      this->numCapacity = this->numElements = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   this->numCapacity = numCapacity;
   this->numElements = 0;
   this->iTail = 0;
   this->iHead = 0;

   // initialize the Queue by calling the default constructor
   for (int i = 0; i < numCapacity; i++)
      data[i] = T();
}

/***************************************************
 * Queue :: Push
 * Insert an item on the end of the Queue
 **************************************************/
template <class T>
void Queue <T> :: push(const T & t) throw (const char *)
{
    int newCapacity;
    int back = iTail;

    if (numCapacity > 0) 
    {
        back = (iTail + 1) % numCapacity;
    }
    // check the capacity if is empty 
    if (numCapacity == empty() || (numCapacity - size()) == 0)
    {
        if (numCapacity == 0) 
        {
            newCapacity = 4; // set 4 even though size is 0
        }

        else 
        {
            newCapacity = (numCapacity * 2);
        }

        // attempt to allocate
        try 
        {
           // create new allocation if the size is full 
             T * newData = new T[numCapacity];
            for (int i = 0; i < size(); i++) 
            {
              int index = (i + iHead) % size();
              newData[i] = data[index];
            }

            delete[] data;
            data = new T[newCapacity];
            numCapacity = newCapacity;

            // correct new allocation for iTail and iHead
            iTail = numElements;
            back = (iTail + 1) % numCapacity;
            iHead = 0;

            // get a copy of the new allocated data
            for (int i= 0; i < numElements; i++) {
                data[i] = newData[i];
            }

            // free allocated memory 
            delete[] newData;     
            newData = newData;       
        }

        catch(std::bad_alloc) 
        {
            throw "ERROR: Unable to allocate a new buffer for queue";
        }
    }

    // increase the tail vale
    data[iTail] = t;
    iTail = back;
    numElements++;
}
#endif // Queue_H