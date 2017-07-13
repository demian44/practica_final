#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ArrayList.h"

// funciones privadas
int resizeUp(ArrayList* this);
int expand(ArrayList* this,int index);
int contract(ArrayList* this,int index);
void quickSortP(void** array,int (*pFunc)(void*,void*), int size, int order);

#define AL_INCREMENT      10
#define AL_INITIAL_VALUE  10
#define Al_SECOND_SCALE 1000
#define AL_LIMIT_OF_INCREASE_PERIODICITY_IN_SECONDS 300
//___________________

/** \brief Allocate a new arrayList with AL_INITIAL_VALUE elements.
 * \param void
 * \return ArrayList* Return (NULL) if Error [if can't allocate memory]
 *                  - (pointer to new arrayList) if ok
 */
ArrayList* al_newArrayList(void) // 1
{
    ArrayList* this;
    ArrayList* returnAux = NULL;
    void* pElements;
    this=(ArrayList *)malloc(sizeof(ArrayList));

    if(this != NULL)
    {
        pElements = malloc(sizeof(void *)*AL_INITIAL_VALUE );
        if(pElements != NULL)
        {
            this->size=0;
            this->pElements=pElements;
            this->reservedSize=AL_INITIAL_VALUE;
            this->lastResizeUp=0;
            this->frecuenseResizeUp=0;
            this->quantityResizeup=0;
            this->add=al_add;
            this->len=al_len;
            this->set=al_set;
            this->remove=al_remove;
            this->clear=al_clear;
            this->clone=al_clone;
            this->get=al_get;
            this->contains=al_contains;
            this->push=al_push;
            this->indexOf=al_indexOf;
            this->isEmpty=al_isEmpty;
            this->pop=al_pop;
            this->subList=al_subList;
            this->filter=al_filter;
            this->containsAll=al_containsAll;
            this->deleteArrayList = al_deleteArrayList;
            this->sort = al_sort;
            returnAux = this;
        }
        else
        {
            free(this);
        }
    }

    return returnAux;
}


/** \brief  Add an element to arrayList and if is
 *          nessesary resize the array
 * \param this ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [this or pElement are NULL pointer] - (0) if Ok
 *
 */
int al_add(ArrayList* this,void* pElement)// 2
{
    int returnAux = -1;
    if(this!=NULL && pElement!= NULL)
    {
        returnAux = 0;
        //if(resizeUp(this)==0)
        if(this->size < this->reservedSize)
        {
            this->size++;
            this->set(this,(this->len(this))-1,pElement);
        }

    }

    return returnAux;
}

/** \brief  Delete arrayList
 * \param this ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [this is NULL pointer] - (0) if Ok
 *
 */
int al_deleteArrayList(ArrayList* this)// 3
{
    int returnAux = -1;
    if(this!=NULL)
    {
        free(this);
        this=NULL;
        returnAux=0;
    }
    return returnAux;
}

/** \brief  Delete arrayList
 * \param this ArrayList* Pointer to arrayList
 * \return int Return length of array or (-1) if Error [this is NULL pointer]
 *
 */
int al_len(ArrayList* this) // 4
{
    int returnAux = -1;
    if(this!=NULL)
        returnAux = this->size;
    return returnAux;
}

/** \brief  Get an element by index
 * \param this ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return void* Return (NULL) if Error [this is NULL pointer or invalid index] - (Pointer to element) if Ok
 *
 */
void* al_get(ArrayList* this, int index)// 5
{
    void* returnAux = NULL;
    if(this!=NULL && index >=0 && index < this->size)
        returnAux =*(this->pElements+index);
    return returnAux;
}

/** \brief  Find if this contains at least one element pElement
 * \param this ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [this or pElement are NULL pointer]
 *                  - ( 0) if Ok but not found a element
 *                  - ( 1) if this list contains at least one element pElement
 *
 */
int al_contains(ArrayList* this, void* pElement) // 6
{
    int index;
    int returnAux = -1;
    if(this!=NULL && pElement!=NULL)
    {
        returnAux=0;
        for(index=0; index<this->size; index++)
        {
            if(pElement==al_get(this,index))
            {
                returnAux=1;
                break;
            }
        }
    }
    return returnAux;
}

/** \brief  Set a element in this at index position
 * \param this ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [this or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 *
 */
int al_set(ArrayList* this, int index,void* pElement) // 7
{
    int returnAux = -1;
    if(this!=NULL && pElement!=NULL && index < (this->size) && index>=0)
    {
        *((this->pElements)+index)=pElement;
        returnAux=0;
    }
    return returnAux;
}

/** \brief  Remove an element by index
 * \param this ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [this is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_remove(ArrayList* this,int index) // 8
{
    int returnAux = -1;
    if(this!=NULL && index < this->size)
        returnAux=contract(this,index);
    return returnAux;
}

/** \brief Removes all of the elements from this list
 * \param this ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [this is NULL pointer]
 *                  - ( 0) if Ok
 */
int al_clear(ArrayList* this) // 9
{
    int returnAux = -1;
    if(this!=NULL && this->size>=0)
    {
        this->size=0;
        returnAux=0;
    }
    return returnAux;
}

/** \brief Returns an array containing all of the elements in this list in proper sequence
 * \param this ArrayList* Pointer to arrayList
 * \return ArrayList* Return  (NULL) if Error [this is NULL pointer]
 *                          - (New array) if Ok
 */
ArrayList* al_clone(ArrayList* this) // 10
{
    ArrayList* returnAux = NULL;
    int i=0;
    if(this!=NULL && this->size>0)
    {
        returnAux=al_newArrayList();
        while(i<(this->size)&& returnAux!=NULL)
        {
            if(-1==returnAux->add(returnAux,this->get(this,i)))
                break;
            i++;
        }
    }
    return returnAux;
}

/** \brief Inserts the element at the specified position
 * \param this ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [this or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_push(ArrayList* this, int index, void* pElement) // 11
{
    int returnAux = -1;
    if(this!=NULL  && pElement!=NULL && index >=0 && index <= this->size)
    {
        if(resizeUp(this)==0)
        {

            expand(this,index);
            *((this->pElements)+index)=pElement;
            returnAux=0;
        }
    }
    return returnAux;
}

/** \brief Returns the index of the first occurrence of the specified element
 * \param this ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [this or pElement are NULL pointer] - (index to element) if Ok
 */
int al_indexOf(ArrayList* this, void* pElement) // 12
{
    int returnAux = -1;
    if(this!=NULL && pElement!=NULL)
    {
        int index;
        for(index=0; index<this->size; index++)
        {
            if(*((this->pElements)+index)==pElement)
            {
                returnAux=index;
                break;
            }

        }
    }

    return returnAux;
}

/** \brief Returns true if this list contains no elements.
 * \param this ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [this is NULL pointer] - (0) if Not Empty - (1) if is Empty
 */
int al_isEmpty(ArrayList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
        if(this->size>0)
            returnAux=0;
        else
            returnAux=1;
    }

    return returnAux;
}

/** \brief Remove the item at the given position in the list, and return it.
 * \param this ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (NULL) if Error [this is NULL pointer or invalid index]
 *                  - ( element pointer) if Ok
 */
void* al_pop(ArrayList* this,int index) // 13
{
    void* returnAux = NULL;
    if(this!=NULL && index>=0 && index<this->size)
    {
        returnAux=al_get(this,index);
        al_remove(this,index);
    }
    return returnAux;
}


/** \brief Returns a new arrayList with a portion of this between the specified
 *         fromIndex, inclusive, and toIndex, exclusive.
 * \param this ArrayList* Pointer to arrayList
 * \param from int Initial index of the element (inclusive)
 * \param to int Final index of the element (exclusive)
 * \return int Return (NULL) if Error [this is NULL pointer or invalid 'from' or invalid 'to']
 *                  - ( pointer to new array) if Ok
 */
ArrayList* al_subList(ArrayList* this,int from,int to) //14
{
    ArrayList* returnAux = NULL;
    int indexFromTo;
    int index;
    if(this!=NULL && from<to && from>=0 && to <=this->size)
    {
        returnAux=al_newArrayList();
        returnAux->size=(to-from);
        resizeUp(returnAux);
        if(returnAux!=NULL)
        {
            for( index=0,indexFromTo=from ; (index+from)<to ; index++,indexFromTo++)
                returnAux->pElements[index]=this->pElements[indexFromTo];
        }

    }
    return returnAux;
}

/** \brief Returns a new arrayList with a portion of this between the specified
 *         fromIndex, inclusive, and toIndex, exclusive.
 * \param this ArrayList* Pointer to arrayList
 * \param from int Initial index of the element (inclusive)
 * \param to int Final index of the element (exclusive)
 * \return int Return (NULL) if Error [this is NULL pointer or invalid 'from' or invalid 'to']
 *                  - ( pointer to new array) if Ok
 */
ArrayList* al_filter(ArrayList* this,int(*fComp)(void*,int),int argu) //14,void* argu
{
    ArrayList* returnAux = NULL;
    int index;
    if(this!=NULL && fComp!=NULL)
    {
        returnAux=al_newArrayList();
        if(returnAux==NULL)
            return returnAux;
        for(index=0; index<this->len(this); index++)
        {
            if(fComp(this->get(this,index),argu))
                returnAux->add(returnAux,this->get(this,index));
        }
    }
    return returnAux;
}
/** \brief Returns true if this list contains all of the elements of this2
 * \param this ArrayList* Pointer to arrayList
 * \param this2 ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [this or this2 are NULL pointer]
 *                  - (0) if Not contains All - (1) if is contains All
 */
int al_containsAll(ArrayList* this,ArrayList* this2)
{
    int returnAux = -1;
    int index;
    if(this!= NULL && this2 != NULL)
    {

        returnAux=0;
        for(index=0; index<this2->size; index++)
        {
            if(1!=al_contains(this,this2->get(this2,index)))
            {
                break;
            }
        }
        if(index==this2->size)
        {
            returnAux=1;
        }
    }
    return returnAux;
}

/** \brief Sorts objects of list, use compare pFunc
 * \param this ArrayList* Pointer to arrayList
 * \param pFunc (*pFunc) Pointer to fuction to compare elements of arrayList
 * \param order int  [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [this or pFunc are NULL pointer]
 *                  - (0) if ok
 */
int al_sort(ArrayList* this, int (*pFunc)(void*,void*), int order)
{
    int returnAux = -1;
    if(this!=NULL && order>=0 && order<2 && pFunc != NULL)
    {
        returnAux=0;
        if(order==0)
            order-=1;
        quickSortP(this->pElements,pFunc,this->size,order);
    }
    return returnAux;
}

/** \brief Sorts objects of list, use compare pFunc
 * \param array void* Pointer to arrayList
 * \param pFunc (*pFunc) Pointer to fuction to compare elements of arrayList
 * \param size extension of arrayList
 * \param order int  [1] indicate UP - [-1] indicate DOWN
 */
void quickSortP(void** array,int (*pFunc)(void*,void*), int size, int order)
{
    void* pivot;
    int i,j;
    void* auxiliar;
    if (size < 2)
        return;
    pivot=array[size/2];
    for(i=0,j=size-1; ; i++,j--)
    {
        while(order==pFunc(pivot,array[i]) && i<size)
            i++;
        while(order==pFunc(array[j],pivot) && j>=0)
            j--;
        if(i>=j)
            break;
        auxiliar  = array[i];
        array[i]=array[j];
        array[j]=auxiliar;
    }
    quickSortP(array,pFunc,i,order);
    quickSortP(array+i,pFunc,size-i,order);
}

/** \brief Increment the number of elements in this in AL_INCREMENT elements.
 * \param this ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [this is NULL pointer or if can't allocate memory]
 *                  - (0) if ok
 */
int resizeUp(ArrayList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
        if((this->size+1)==this->reservedSize)
            returnAux=arrayListRealloc(this,sizeof(this->size+AL_INCREMENT));
        else if(this->size>this->reservedSize)
            returnAux=arrayListRealloc(this,sizeof(this->size));

        returnAux=0;
    }
    return returnAux;
}


/** \brief Increment the number of elements in this in AL_INCREMENT elements.
 * \param this ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [this is NULL pointer or if can't allocate memory]
 *                  - (0) if ok
 */
int resizeDown(ArrayList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
        if(this->reservedSize-this->size>(AL_INCREMENT*2))
            returnAux=arrayListRealloc(this,sizeof(this->size));
        else
            returnAux=0;
    }
    return returnAux;
}

/** \brief  Expand an array list
 * \param this ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [this is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int expand(ArrayList* this,int index)
{
    int returnAux = -1;
    int auxIndex;
    if(this!=NULL && index>=0 && index <= this->size)
    {
        for(auxIndex=this->size; auxIndex>index; auxIndex--)
            this->pElements[auxIndex]=this->pElements[auxIndex-1];
        this->size++;
        returnAux=0;
    }
    return returnAux;
}

/** \brief  Contract an array list
 * \param this ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [this is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int contract(ArrayList* this,int index)
{
    int returnAux = -1;
    if(this!=NULL && index>=0 && index < this->size)
    {
        returnAux=0;
        for( ; index<(this->size-1); index++)
            this->pElements[index]=this->pElements[index+1];
        this->size--;
    }
    return returnAux;
}

/**\brief modify the size of the reserved memory
 * \param this ArrayList* Pointer to arrayList
 * \param new size of the arraylist
 * \return int Return (-1) if Error [this is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int arrayListRealloc(ArrayList* this, int newSize)
{
    int returnAux=-1;
    void* auxThis;
    auxThis=realloc(this->pElements,newSize);
    if(auxThis!=NULL)
    {
        this->pElements=auxThis;
        returnAux=0;
    }
    return returnAux;
}

/**\brief if is necessary, increment the scale of increase of the array
 * \param this ArrayList* Pointer to arrayList
 * \return int Return ( 0) if don't increase the scale of increase
 *                  - ( 1) if increase the scale of increase
 */
int incrementScaleIncrease(ArrayList* this)
{
    int auxReturn=0;
    long int ingresoActuaal=clock()/Al_SECOND_SCALE;
    this->quantityResizeup++;
    if(this->quantityResizeup==1)
    {
        this->frecuenseResizeUp=ingresoActuaal;
        this->lastResizeUp=ingresoActuaal;
    }
    else if(this->quantityResizeup<3)
    {
        this->frecuenseResizeUp=(ingresoActuaal-this->lastResizeUp+this->frecuenseResizeUp)/2;
        this->lastResizeUp=ingresoActuaal;
    }
    else
    {
        this->frecuenseResizeUp=(ingresoActuaal+this->frecuenseResizeUp)/2;
        if((ingresoActuaal-this->lastResizeUp)<AL_LIMIT_OF_INCREASE_PERIODICITY_IN_SECONDS)
        {
            auxReturn=1;
            this->quantityResizeup=0;
        }
        else
            this->quantityResizeup=0;
    }
    return auxReturn;
}
