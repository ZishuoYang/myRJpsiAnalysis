#ifndef MPATEL_TupleToolTagDiscardDstMu_H
#define MPATEL_TupleToolTagDiscardDstMu_H 1

// Include files
// from Gaudi
#include "DecayTreeTupleBase/TupleToolBase.h"
#include "Kernel/IParticleTupleTool.h"            // Interface

class IDVAlgorithm;
class IDistanceCalculator;
class IVertexFit;
class ILifetimeFitter;

namespace LHCb {
  class Particle;
  class Vertex;
}

/** @class TupleToolTagDiscardDstMu TupleToolTagDiscardDstMu.h
 *
 * \brief Fill isolation information for DecayTreeTuple
 *
 * - head_NOPARTWITHINDCHI2WDW : no. of non-signal particles that when added to vertex give delta chi2 < specified window
 * - head_NOPARTWITHINCHI2WDW : no. of non-signal particles that when added to vertex give chi2 < specified window
 * head_SMALLESTCHI2: chi2 of smallest chi2 combination with any of the input Particles
 * head_SMALLESTDELTACHI2: delta chi2 of smallest delta chi2 combination with any of the input Particles
 *
 * \sa DecayTreeTuple
 *
 *  @todo Maybe one should get Tracks instead of Particles?
 *
 *  @author Mitesh Patel, Patrick Koppenburg
 *  @date   2008-04-15
 */
class TupleToolTagDiscardDstMu : public TupleToolBase,
                          virtual public IParticleTupleTool
{

public:

  /// Standard constructor
  TupleToolTagDiscardDstMu( const std::string& type,
                     const std::string& name,
                     const IInterface* parent);

  virtual ~TupleToolTagDiscardDstMu( ){}; ///< Destructor

  virtual StatusCode initialize();

  StatusCode fill( const LHCb::Particle*
                   , const LHCb::Particle*
                   , const std::string&
                   , Tuples::Tuple& );

private:

  const LHCb::Vertex* originVertex( const  LHCb::Particle*
                                    , const LHCb::Particle* ) const;

private:

  IDVAlgorithm* m_dva;
  const IDistanceCalculator* m_dist;
  const IVertexFit* m_pVertexFit;
  ILifetimeFitter* m_ltfit; 
  std::string m_outputSuffix;
  int m_pri1;
  int m_pri2;
  int m_pri3;
  int m_sec1;
  int m_sec2;
  int m_sec3;
  int m_ter1;
  int m_ter2;
  int m_ter3;
  int m_priDOCA;
  int m_secDOCA;
  int m_terDOCA;
  int m_priexDOCA1;
  int m_secexDOCA1;
  int m_terexDOCA1;
  int m_priexDOCA2;
  int m_secexDOCA2;
  int m_terexDOCA2;
  int m_TimePID;
  bool m_Dstar;
  bool m_discSlow;
  std::string m_typeVertexFit;
  std::vector<std::string> m_inputParticles;

};

#endif // MPATEL_TUPLETOOLGEOMETRY_H
