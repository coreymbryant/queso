/* uq/libs/mcmc/inc/uqVectorRealizer.h
 *
 * Copyright (C) 2008 The PECOS Team, http://www.ices.utexas.edu/centers/pecos
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef __UQ_REALIZER_H__
#define __UQ_REALIZER_H__

#include <uqVectorSequence.h>
#include <uqEnvironment.h>
#include <math.h>

//*****************************************************
// Classes to accomodate a probability density routine.
//*****************************************************

//*****************************************************
// Base class
//*****************************************************
template<class V, class M>
class uqBaseVectorRealizerClass {
public:
           uqBaseVectorRealizerClass(double (*routinePtr)(const void* routineDataPtr, V& nextParamValues),
                                     const void*  routineDataPtr,
                                     unsigned int period);
           uqBaseVectorRealizerClass(const uqBaseVectorSequenceClass<V>* chain);
  virtual ~uqBaseVectorRealizerClass();

  virtual unsigned int period     ()               const;
  virtual void         realization(V& paramValues) const;

protected:
  double (*m_routinePtr)(const void* routineDataPtr, V& nextParamValues);
  const void*                         m_routineDataPtr;
  unsigned int                        m_period;

  const uqBaseVectorSequenceClass<V>* m_chain;
  mutable unsigned int                m_currentChainPos;
};

template<class V, class M>
uqBaseVectorRealizerClass<V,M>::uqBaseVectorRealizerClass(
  double (*routinePtr)(const void* routineDataPtr, V& nextParamValues),
  const void*  routineDataPtr,
  unsigned int period)
  :
  m_routinePtr     (routinePtr),
  m_routineDataPtr (routineDataPtr),
  m_period         (period),
  m_chain          (NULL),
  m_currentChainPos(0)
{
}

template<class V, class M>
uqBaseVectorRealizerClass<V,M>::uqBaseVectorRealizerClass(
  const uqBaseVectorSequenceClass<V>* chain)
  :
  m_routinePtr     (NULL),
  m_routineDataPtr (NULL),
  m_period         (chain->sequenceSize()),
  m_chain          (chain),
  m_currentChainPos(0)
{
}

template<class V, class M>
uqBaseVectorRealizerClass<V,M>::~uqBaseVectorRealizerClass()
{
}

template<class V, class M>
unsigned int
uqBaseVectorRealizerClass<V,M>::period() const
{
  return m_period;
}

template<class V, class M>
void
uqBaseVectorRealizerClass<V,M>::realization(V& nextParamValues) const
{
  if (m_routinePtr) {
    m_routinePtr(m_routineDataPtr, nextParamValues);
  }
  else {
    m_chain->getPositionValues(m_currentChainPos++,nextParamValues);
  }

  return;
}
#endif // __UQ_REALIZER_H__
