/* FILE NAME  : t04list.cpp
 * PROGRAMMER : ND4
 * LAST UPDATE: 20.07.2021
 * PURPOSE    : Work with lists, classes and personal namespace
 */

/* Input/output stream */
#include <iostream>

/* Common c/c++ header */
#include <commondf.h>

/* Disable no-matter warning */
#pragma warning(disable: 26495)

/* Debug memory allocation support */ 
#ifndef NDEBUG 
# define _CRTDBG_MAP_ALLOC
# include  <crtdbg.h>
# define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

static class __Dummy 
{ 
public: 
  /* Class constructor */
  __Dummy( VOID ) 
  { 
    SetDbgMemHooks(); 
  } /* End of '__Dummy' constructor */
} __ooppss;
#endif /* _DEBUG */ 

#ifdef _DEBUG 
# ifdef _CRTDBG_MAP_ALLOC 
#   define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
# endif /* _CRTDBG_MAP_ALLOC */ 
#endif /* _DEBUG */

/* Useful namespace */
namespace nd4
{
  /* Linear single-connected list handle class */
  template <typename Type>
  class list
  {
  private:
    struct entry
    {
      Type Data;
      entry *Next;

      entry(Type NewD, entry *NewN = nullptr) :
          Data(NewD), Next(NewN)
      {
      }
    } *Start;
  public:

    /* List construction function.
     * ARGUMENTS:
     *   - None.
    */
    list( VOID )
    {
      Start = nullptr;
    } /* End of 'list' function */

    /* List construction function.
     * ARGUMENTS:
     *   - List value:
     *       const list &val;
    */
    list( const list &val )
    {
      entry *ptr = val.Start;

      if (Start != nullptr)
        Clear();

      entry **tmptr = &Start;

      try
      {
        while (ptr != nullptr)
        {
          *tmptr = new entry(ptr->Data);
          tmptr = &(*tmptr)->Next;
          ptr = ptr->Next;
        }
      }
      catch(std::bad_alloc)
      {
        OutputDebugString(L"Unable to allocate memory");
      }
    } /* End of 'list' function */

    /* List deconstruction function.
     * ARGUMENTS:
     *   - None.
    */
    ~list( VOID )
    {
      while (Start != nullptr)
      {
        entry* old = Start;

        Start = Start->Next;
        delete old;
      }
    } /* End of '~list' function */

    /* List add into front function.
     * ARGUMENTS:
     *   - Data value:
     *       Type NewD;
     * RETURNS:
     * (list &) result list.
    */
    list & PushFront( Type NewD )
    {
      try
      {
        Start = new entry(NewD, Start);
      }
      catch(std::bad_alloc)
      {
        OutputDebugString(L"Unable to allocate memory");
      }

      return *this;
    } /* End of 'PushFront' function */

    /* List add into back function.
     * ARGUMENTS:
     *   - Data value:
     *       Type NewD;
     * RETURNS:
     * (list &) result list.
    */
    list & PushBack( Type NewD )
    {
      entry **ptr = &Start;

      while (*ptr != nullptr)
        ptr = &(*ptr)->Next;

      try
      {
      *ptr = new entry(NewD, *ptr);
      }
      catch(std::bad_alloc)
      {
        OutputDebugString(L"Unable to allocate memory");
      }

      return *this;
    } /* End of 'PushBack' function */

    /* List delete from front function.
     * ARGUMENTS:
     *   - Ptr to variable to save old value:
     *       Type *old;
     * RETURNS:
     * (list &) result list.
    */
    BOOL PopFront( Type *old = nullptr )
    {
      entry *ptr = Start;

      Start = Start->Next;
      if (old != nullptr)
        *old = ptr->Data;
      delete ptr;
      return TRUE;
    } /* End of 'PopFront' function */

    /* List delete from back function.
     * ARGUMENTS:
     *   - Ptr to variable to save old value:
     *       Type *old;
     * RETURNS:
     * (list &) result list.
    */
    BOOL PopBack( Type *old = nullptr )
    {
      entry **ptr = &Start;

      if (*ptr == nullptr)
        return FALSE;

      while ((*ptr)->Next != nullptr)
        ptr = &(*ptr)->Next;

      if (old != nullptr)
        *old = (*ptr)->Data;

      delete *ptr;
      *ptr = nullptr;

      return TRUE;
    } /* End of 'PopBack' function */

    /* List clear function.
     * ARGUMENTS:
     *   - None.
     * RETURNS:
     * (VOID) None.
    */
    VOID Clear( VOID )
    {
      while (Start != nullptr)
      {
        entry *old;
        old = Start;

        Start = Start->Next;
        delete old;
      }
    } /* End of 'Clear' function */

    /* List equality function.
     * ARGUMENTS:
     *   - List value:
     *       const list &val;
     * RETURNS:
     * (list &) result list.
    */
    list & operator = ( const list &val )
    {
      entry *ptr = val.Start;

      if (Start != nullptr)
        Clear();

      entry **tmptr = &Start;

      try
      {
        while (ptr != nullptr)
        {
          *tmptr = new entry(ptr->Data);
          tmptr = &(*tmptr)->Next;
          ptr = ptr->Next;
        }
      }
      catch(std::bad_alloc)
      {
        OutputDebugString(L"Unable to allocate memory");
      }

      return *this;
    } /* End of 'operator ='  function */

    /* List equality function.
     * ARGUMENTS:
     *   - List value:
     *       const list &val;
     * RETURNS:
     * (list &) result list.
    */
    list & operator += ( const list &val )
    {
      entry *ptr = val.Start;

      while (ptr != nullptr)
      {
        PushBack(ptr->Data);

        ptr = ptr->Next;
      }

      return *this;
    } /* End of 'operator ='  function */

    /* List displaying function.
     * ARGUMENTS:
     *   - None.
     * RETURNS:
     * (VOID) None.
    */
    VOID Display( VOID )
    {
      entry *ptr = Start;

      while (ptr != nullptr)
      {
          std::cout << ptr->Data;
          ptr = ptr->Next;
          std::cout << " ";
      }
      std::cout << "\n";
    } /* End of 'Display' function */

    /* List clear check function.
     * ARGUMENTS:
     *   - None.
     * RETURNS:
     * (bool) TRUE/FALSE.
    */
    bool IsEmpty( VOID )
    {
      return Start == nullptr;
    } /* End of 'IsEmpty' function */
  }; /* End of 'list' class */
}; /* End of 'nd4' namespace */

/* Program main function.
 * ARGUMENTS:
 *   - None.
 * RETURNS:
 * (INT) Code to OS.
*/
INT main( VOID )
{
  nd4::list<double> L;
  
  L.PushFront(30.46);
  L.PushFront(102);
  L.PushBack(0.23);
  L.PushBack(11);
  L.Display();

 } /* End of 'main' function */

/* END OF 't04list.cpp' FILE */