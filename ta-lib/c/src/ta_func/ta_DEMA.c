/* TA-LIB Copyright (c) 1999-2003, Mario Fortier
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 *
 * - Neither name of author nor the names of its contributors
 *   may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* List of contributors:
 *
 *  Initial  Name/description
 *  -------------------------------------------------------------------
 *  MF       Mario Fortier
 *
 *
 * Change history:
 *
 *  MMDDYY BY   Description
 *  -------------------------------------------------------------------
 *  010102 MF   Template creation.
 *  052603 MF   Adapt code to compile with .NET Managed C++
 *
 */

/**** START GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
/* All code within this section is automatically
 * generated by gen_code. Any modification will be lost
 * next time gen_code is run.
 */
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */    #using <mscorlib.dll>
/* Generated */    #include "Core.h"
/* Generated */    namespace TA { namespace Lib {
/* Generated */ #else
/* Generated */    #include <string.h>
/* Generated */    #include <math.h>
/* Generated */    #include "ta_func.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #ifndef TA_UTILITY_H
/* Generated */    #include "ta_utility.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #ifndef TA_MEMORY_H
/* Generated */    #include "ta_memory.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #define TA_PREFIX(x) TA_##x
/* Generated */ #define INPUT_TYPE   double
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ int Core::DEMA_Lookback( int           optInTimePeriod_0 )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #else
/* Generated */ int TA_DEMA_Lookback( int           optInTimePeriod_0 )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #endif
/**** END GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
{
   /* insert lookback code here. */

   /* Get lookback for one EMA.
    * Multiply by two (because double smoothing).
    */
   return TA_EMA_Lookback( optInTimePeriod_0 ) * 2;
}

/**** START GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
/*
 * TA_DEMA - Double Exponential Moving Average
 * 
 * Input  = double
 * Output = double
 * 
 * Optional Parameters
 * -------------------
 * optInTimePeriod_0:(From 2 to 100000)
 *    Number of period
 * 
 * 
 */
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ enum Core::TA_RetCode Core::DEMA( int    startIdx,
/* Generated */                                   int    endIdx,
/* Generated */                                   double       inReal_0 __gc [],
/* Generated */                                   int           optInTimePeriod_0, /* From 2 to 100000 */
/* Generated */                                   [OutAttribute]Int32 *outBegIdx,
/* Generated */                                   [OutAttribute]Int32 *outNbElement,
/* Generated */                                   double        outReal_0 __gc [] )
/* Generated */ #else
/* Generated */ TA_RetCode TA_DEMA( int    startIdx,
/* Generated */                     int    endIdx,
/* Generated */                     const double inReal_0[],
/* Generated */                     int           optInTimePeriod_0, /* From 2 to 100000 */
/* Generated */                     int          *outBegIdx,
/* Generated */                     int          *outNbElement,
/* Generated */                     double        outReal_0[] )
/* Generated */ #endif
/**** END GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
{
   /* Insert local variables here. */
   ARRAY_REF(firstEMA);
   ARRAY_REF(secondEMA);
   double k;
   int firstEMABegIdx, firstEMANbElement;
   int secondEMABegIdx, secondEMANbElement;
   int tempInt, outIdx, firstEMAIdx, lookbackTotal, lookbackEMA;
   TA_RetCode retCode;

/**** START GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */ 
/* Generated */    /* Validate the requested output range. */
/* Generated */    if( startIdx < 0 )
/* Generated */       return TA_OUT_OF_RANGE_START_INDEX;
/* Generated */    if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */       return TA_OUT_OF_RANGE_END_INDEX;
/* Generated */ 
/* Generated */    /* Validate the parameters. */
/* Generated */    if( !inReal_0 ) return TA_BAD_PARAM;
/* Generated */    /* min/max are checked for optInTimePeriod_0. */
/* Generated */    if( (int)optInTimePeriod_0 == TA_INTEGER_DEFAULT )
/* Generated */       optInTimePeriod_0 = 30;
/* Generated */    else if( ((int)optInTimePeriod_0 < 2) || ((int)optInTimePeriod_0 > 100000) )
/* Generated */       return TA_BAD_PARAM;
/* Generated */ 
/* Generated */    if( outReal_0 == NULL )
/* Generated */       return TA_BAD_PARAM;
/* Generated */ 
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/

   /* Insert TA function code here. */

   /* For an explanation of this function, please read
    * 
    * Stocks & Commodities V. 12:1 (11-19): 
    *   Smoothing Data With Faster Moving Averages
    * Stocks & Commodities V. 12:2 (72-80): 
    *   Smoothing Data With Less Lag
    *
    * Both magazine articles written by Patrick G. Mulloy
    *
    * Essentially, a DEMA of time serie 't' is:
    *   EMA2 = EMA(EMA(t,period),period)
    *   DEMA = 2*EMA(t,period)- EMA2
    *
    * DEMA offers a moving average with less lags then the
    * traditional EMA.
    *
    * Do not confuse a DEMA with the EMA2. Both are called 
    * "Double EMA" in the litterature, but EMA2 is a simple
    * EMA of an EMA, while DEMA is a compostie of a single
    * EMA with EMA2.
    *
    * TEMA is very similar (and from the same author).
    */

   /* Will change only on success. */
   *outNbElement = 0;
   *outBegIdx    = 0;

   /* Adjust startIdx to account for the lookback period. */
   lookbackEMA = TA_EMA_Lookback( optInTimePeriod_0 );
   lookbackTotal = lookbackEMA * 2;

   if( startIdx < lookbackTotal )
      startIdx = lookbackTotal;

   /* Make sure there is still something to evaluate. */
   if( startIdx > endIdx )
      return TA_SUCCESS; 

   /* Allocate a temporary buffer for the firstEMA.
    *
    * When possible, re-use the outputBuffer for temp
    * calculation.
    */
   #if defined(USE_SINGLE_PRECISION_INPUT)
      tempInt = lookbackTotal+(endIdx-startIdx)+1;
      ARRAY_ALLOC(firstEMA, tempInt );
      if( !firstEMA )
         return TA_ALLOC_ERR;
   #else
      if( inReal_0 == outReal_0 )
         firstEMA = outReal_0;
      else
      {
         tempInt = lookbackTotal+(endIdx-startIdx)+1;
         ARRAY_ALLOC(firstEMA, tempInt );
         if( !firstEMA )
            return TA_ALLOC_ERR;
      }
   #endif

   /* Calculate the first EMA */   
   k = PER_TO_K(optInTimePeriod_0);
   retCode = TA_PREFIX(INT_EMA)( startIdx-lookbackEMA, endIdx, inReal_0,
                                 optInTimePeriod_0, k,
                                 &firstEMABegIdx, &firstEMANbElement, firstEMA );
   
   /* Verify for failure or if not enough data after
    * calculating the first EMA.
    */
   if( (retCode != TA_SUCCESS) || (firstEMANbElement == 0) )
   {
      ARRAY_FREE_COND( firstEMA != outReal_0, firstEMA );
      return retCode;
   }

   /* Allocate a temporary buffer for storing the EMA of the EMA. */
   ARRAY_ALLOC(secondEMA,firstEMANbElement);

   if( !secondEMA )
   {
      ARRAY_FREE_COND( firstEMA != outReal_0, firstEMA );
      return TA_ALLOC_ERR;
   }

   retCode = TA_INT_EMA( 0, firstEMANbElement-1, firstEMA,
                         optInTimePeriod_0, k,
                         &secondEMABegIdx, &secondEMANbElement, secondEMA );

   /* Return empty output on failure or if not enough data after
    * calculating the second EMA.
    */
   if( (retCode != TA_SUCCESS) || (secondEMANbElement == 0) )      
   {
      #if defined(USE_SINGLE_PRECISION_INPUT)
         ARRAY_FREE( firstEMA );
      #else
         ARRAY_FREE_COND( firstEMA != outReal_0, firstEMA );
      #endif
      ARRAY_FREE( secondEMA );
      return retCode;
   }

   /* Iterate through the second EMA and write the DEMA into
    * the output.
    */
   firstEMAIdx = secondEMABegIdx;
   outIdx = 0;
   while( outIdx < secondEMANbElement ) 
   {
      outReal_0[outIdx] = (2.0*firstEMA[firstEMAIdx++]) - secondEMA[outIdx];
      outIdx++;
   }

   #if defined(USE_SINGLE_PRECISION_INPUT)
      ARRAY_FREE( firstEMA );
   #else
      ARRAY_FREE_COND( firstEMA != outReal_0, firstEMA );
   #endif
   ARRAY_FREE( secondEMA );

   /* Succeed. Indicate where the output starts relative to
    * the caller input.
    */
   *outBegIdx    = firstEMABegIdx + secondEMABegIdx;
   *outNbElement = outIdx;

   return TA_SUCCESS;
}


/**** START GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #define  USE_SINGLE_PRECISION_INPUT
/* Generated */ #if !defined( _MANAGED )
/* Generated */    #undef   TA_PREFIX
/* Generated */    #define  TA_PREFIX(x) TA_S_##x
/* Generated */ #endif
/* Generated */ #undef   INPUT_TYPE
/* Generated */ #define  INPUT_TYPE float
/* Generated */ #if defined( _MANAGED )
/* Generated */ enum Core::TA_RetCode Core::DEMA( int    startIdx,
/* Generated */                                   int    endIdx,
/* Generated */                                   float        inReal_0 __gc [],
/* Generated */                                   int           optInTimePeriod_0, /* From 2 to 100000 */
/* Generated */                                   [OutAttribute]Int32 *outBegIdx,
/* Generated */                                   [OutAttribute]Int32 *outNbElement,
/* Generated */                                   double        outReal_0 __gc [] )
/* Generated */ #else
/* Generated */ TA_RetCode TA_S_DEMA( int    startIdx,
/* Generated */                       int    endIdx,
/* Generated */                       const float  inReal_0[],
/* Generated */                       int           optInTimePeriod_0, /* From 2 to 100000 */
/* Generated */                       int          *outBegIdx,
/* Generated */                       int          *outNbElement,
/* Generated */                       double        outReal_0[] )
/* Generated */ #endif
/* Generated */ {
/* Generated */    ARRAY_REF(firstEMA);
/* Generated */    ARRAY_REF(secondEMA);
/* Generated */    double k;
/* Generated */    int firstEMABegIdx, firstEMANbElement;
/* Generated */    int secondEMABegIdx, secondEMANbElement;
/* Generated */    int tempInt, outIdx, firstEMAIdx, lookbackTotal, lookbackEMA;
/* Generated */    TA_RetCode retCode;
/* Generated */  #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */     if( startIdx < 0 )
/* Generated */        return TA_OUT_OF_RANGE_START_INDEX;
/* Generated */     if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */        return TA_OUT_OF_RANGE_END_INDEX;
/* Generated */     if( !inReal_0 ) return TA_BAD_PARAM;
/* Generated */     if( (int)optInTimePeriod_0 == TA_INTEGER_DEFAULT )
/* Generated */        optInTimePeriod_0 = 30;
/* Generated */     else if( ((int)optInTimePeriod_0 < 2) || ((int)optInTimePeriod_0 > 100000) )
/* Generated */        return TA_BAD_PARAM;
/* Generated */     if( outReal_0 == NULL )
/* Generated */        return TA_BAD_PARAM;
/* Generated */  #endif 
/* Generated */    *outNbElement = 0;
/* Generated */    *outBegIdx    = 0;
/* Generated */    lookbackEMA = TA_EMA_Lookback( optInTimePeriod_0 );
/* Generated */    lookbackTotal = lookbackEMA * 2;
/* Generated */    if( startIdx < lookbackTotal )
/* Generated */       startIdx = lookbackTotal;
/* Generated */    if( startIdx > endIdx )
/* Generated */       return TA_SUCCESS; 
/* Generated */    #if defined(USE_SINGLE_PRECISION_INPUT)
/* Generated */       tempInt = lookbackTotal+(endIdx-startIdx)+1;
/* Generated */       ARRAY_ALLOC(firstEMA, tempInt );
/* Generated */       if( !firstEMA )
/* Generated */          return TA_ALLOC_ERR;
/* Generated */    #else
/* Generated */       if( inReal_0 == outReal_0 )
/* Generated */          firstEMA = outReal_0;
/* Generated */       else
/* Generated */       {
/* Generated */          tempInt = lookbackTotal+(endIdx-startIdx)+1;
/* Generated */          ARRAY_ALLOC(firstEMA, tempInt );
/* Generated */          if( !firstEMA )
/* Generated */             return TA_ALLOC_ERR;
/* Generated */       }
/* Generated */    #endif
/* Generated */    k = PER_TO_K(optInTimePeriod_0);
/* Generated */    retCode = TA_PREFIX(INT_EMA)( startIdx-lookbackEMA, endIdx, inReal_0,
/* Generated */                                  optInTimePeriod_0, k,
/* Generated */                                  &firstEMABegIdx, &firstEMANbElement, firstEMA );
/* Generated */    if( (retCode != TA_SUCCESS) || (firstEMANbElement == 0) )
/* Generated */    {
/* Generated */       ARRAY_FREE_COND( firstEMA != outReal_0, firstEMA );
/* Generated */       return retCode;
/* Generated */    }
/* Generated */    ARRAY_ALLOC(secondEMA,firstEMANbElement);
/* Generated */    if( !secondEMA )
/* Generated */    {
/* Generated */       ARRAY_FREE_COND( firstEMA != outReal_0, firstEMA );
/* Generated */       return TA_ALLOC_ERR;
/* Generated */    }
/* Generated */    retCode = TA_INT_EMA( 0, firstEMANbElement-1, firstEMA,
/* Generated */                          optInTimePeriod_0, k,
/* Generated */                          &secondEMABegIdx, &secondEMANbElement, secondEMA );
/* Generated */    if( (retCode != TA_SUCCESS) || (secondEMANbElement == 0) )      
/* Generated */    {
/* Generated */       #if defined(USE_SINGLE_PRECISION_INPUT)
/* Generated */          ARRAY_FREE( firstEMA );
/* Generated */       #else
/* Generated */          ARRAY_FREE_COND( firstEMA != outReal_0, firstEMA );
/* Generated */       #endif
/* Generated */       ARRAY_FREE( secondEMA );
/* Generated */       return retCode;
/* Generated */    }
/* Generated */    firstEMAIdx = secondEMABegIdx;
/* Generated */    outIdx = 0;
/* Generated */    while( outIdx < secondEMANbElement ) 
/* Generated */    {
/* Generated */       outReal_0[outIdx] = (2.0*firstEMA[firstEMAIdx++]) - secondEMA[outIdx];
/* Generated */       outIdx++;
/* Generated */    }
/* Generated */    #if defined(USE_SINGLE_PRECISION_INPUT)
/* Generated */       ARRAY_FREE( firstEMA );
/* Generated */    #else
/* Generated */       ARRAY_FREE_COND( firstEMA != outReal_0, firstEMA );
/* Generated */    #endif
/* Generated */    ARRAY_FREE( secondEMA );
/* Generated */    *outBegIdx    = firstEMABegIdx + secondEMABegIdx;
/* Generated */    *outNbElement = outIdx;
/* Generated */    return TA_SUCCESS;
/* Generated */ }
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ }} // Close namespace TA.Lib
/* Generated */ #endif
/**** END GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/

