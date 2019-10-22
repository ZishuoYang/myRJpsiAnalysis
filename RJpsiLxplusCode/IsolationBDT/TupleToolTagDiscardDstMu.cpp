// Include files

// from Gaudi
#include "GaudiKernel/ToolFactory.h"

// local
#include "TupleToolTagDiscardDstMu.h"

#include <Kernel/GetIDVAlgorithm.h>
#include <Kernel/IDVAlgorithm.h>
#include <Kernel/IDistanceCalculator.h>
#include <Kernel/IVertexFit.h>
#include <Kernel/ILifetimeFitter.h>
#include "GaudiAlg/Tuple.h"
#include "GaudiAlg/TupleObj.h"

#include "Event/Particle.h"

using namespace LHCb;

//-----------------------------------------------------------------------------
// Implementation file for class : TupleToolTagDiscardDstMu
//
// @author Mitesh Patel, Patrick Koppenburg
// @date   2008-04-15
//-----------------------------------------------------------------------------

// Declaration of the Tool Factory
// actually acts as a using namespace TupleTool
DECLARE_TOOL_FACTORY( TupleToolTagDiscardDstMu )

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
  TupleToolTagDiscardDstMu::TupleToolTagDiscardDstMu( const std::string& type,
                                        const std::string& name,
                                        const IInterface* parent )
    : TupleToolBase ( type, name , parent )
    , m_dva(0)
    , m_dist(0)
    , m_pVertexFit(0)
{
  declareInterface<IParticleTupleTool>(this);
  declareProperty( "Primary1", m_pri1 = -1);
  declareProperty( "Primary2", m_pri2 = -1);
  declareProperty( "Primary3", m_pri3 = -1);
  declareProperty( "PrimaryForDOCA", m_priDOCA = 2);
  declareProperty( "SecondaryForDOCA", m_secDOCA = -1);
  declareProperty( "TertiaryForDOCA", m_terDOCA = -1);
  declareProperty( "Secondary1", m_sec1 = -1);
  declareProperty( "Secondary2", m_sec2 = -1);
  declareProperty( "Secondary3", m_sec3 = -1);
  declareProperty( "Tertiary1", m_ter1 = -1);
  declareProperty( "Tertiary2", m_ter2 = -1);
  declareProperty( "Tertiary3", m_ter3 = -1);
  declareProperty( "PrimaryExtraDOCA1", m_priexDOCA1 = -1);
  declareProperty( "SecondaryExtraDOCA1", m_secexDOCA1 = -1);
  declareProperty( "TertiaryExtraDOCA1", m_terexDOCA1 = -1);
  declareProperty( "PrimaryExtraDOCA2", m_priexDOCA2 = -1);
  declareProperty( "SecondaryExtraDOCA2", m_secexDOCA2 = -1);
  declareProperty( "TertiaryExtraDOCA2", m_terexDOCA2 = -1);
  declareProperty( "Dstar", m_Dstar = true);
  declareProperty( "DiscardSlow", m_discSlow = false);
  declareProperty( "TimePID", m_TimePID = 421);
  declareProperty("OutputSuffix", m_outputSuffix = "" );
}

//=============================================================================

StatusCode TupleToolTagDiscardDstMu::initialize()
{
  const StatusCode sc = TupleToolBase::initialize();
  if ( sc.isFailure() ) return sc;

  m_dva = Gaudi::Utils::getIDVAlgorithm ( contextSvc(), this ) ;
  if (!m_dva) return Error("Couldn't get parent DVAlgorithm",
                           StatusCode::FAILURE);

  m_dist = m_dva->distanceCalculator ();
  if( !m_dist ){
    Error("Unable to retrieve the IDistanceCalculator tool");
    return StatusCode::FAILURE;
  }

  //m_pVertexFit= m_dva->vertexFitter();
  m_pVertexFit  = tool<IVertexFit>("LoKi::VertexFitter",this);
  if( !m_pVertexFit ){
    Error("Unable to retrieve the IVertexFit tool");
    return StatusCode::FAILURE;
  }
  m_ltfit = tool<ILifetimeFitter>( "PropertimeFitter", this );
  if( !m_ltfit ){
    Error("Unable to retrieve the ILifetimeFitter tool");
    return StatusCode::FAILURE;
  }

  return sc;
}

//=============================================================================

StatusCode TupleToolTagDiscardDstMu::fill( const Particle* mother
                                    , const Particle* P
                                    , const std::string& head
                                    , Tuples::Tuple& tuple )
{

  const std::string prefix=fullName(head);
  Assert( P && mother && m_dist
          , "This should not happen, you are inside TupleToolTagDiscardDstMu.cpp :(" );


  bool test=true;
  // --------------------------------------------------

  // find the origin vertex. Either the primary or the origin in the
  // decay
  /*
    const VertexBase* vtx = 0;
    if( mother != P ) vtx = originVertex( mother, P );
    if( !vtx ){
    Error("Can't retrieve the origin vertex for " + prefix );
    return StatusCode::FAILURE;
    }
  */
  const LHCb::Vertex* vtx;
  if (P->isBasicParticle() || isPureNeutralCalo(P) ){
    vtx = mother->endVertex();
  }
  else{
    vtx = P->endVertex();
  }
  debug()<<"vertex for P, ID " <<P->particleID().pid()<<" = " <<vtx<<" at "<<vtx->position()<<  endmsg;
  if( !vtx ){
    Error("Can't retrieve the  vertex for " + prefix );
    return StatusCode::FAILURE;
  }

  // The vertex chi2 of the composite particle being tested
  double vtxChi2 = vtx->chi2();

  //--------------------------------------------------
  // Get all the particle's final states
  LHCb::Particle::ConstVector source;
  LHCb::Particle::ConstVector target;
  LHCb::Particle::ConstVector finalStates;
  LHCb::Particle::ConstVector parts;
  LHCb::Particle::ConstVector parts2VertexMu;
  LHCb::Particle::ConstVector parts2VertexTau;
  LHCb::Particle::ConstVector secondaryparts;
  LHCb::Particle::ConstVector tertiaryparts;
  parts2VertexMu.clear();
  parts2VertexTau.clear();
  secondaryparts.clear();
  parts.clear();

  int i1=0;
  const LHCb::Particle *mu, *pislow, *muMu, *tauMu, *D;
  LHCb::Particle * a1;
  bool foundD = false;
  LHCb::Particle *newD;

  LHCb::Particle::ConstVector bDaughters = mother->daughtersVector();
//Mu loop
int iloop = 0;
for( LHCb::Particle::ConstVector::const_iterator itmp = bDaughters.begin(); 
             itmp!=bDaughters.end(); itmp++){
	     iloop++;

	     if (iloop == 1){
		int iloop2 = 0;

  LHCb::Particle::ConstVector DstDaughters = (*itmp)->daughtersVector();
        for( LHCb::Particle::ConstVector::const_iterator itmp2 = DstDaughters.begin(); 
             itmp2!=DstDaughters.end(); itmp2++){
			iloop2++;
			if (iloop2 == 2)  pislow = (*itmp2);
			if (iloop2 == 1)  {D=(*itmp2);parts2VertexMu.push_back((*itmp2));}
		}// inner for loop
		} //if
	     if (iloop == 2){
		muMu=(*itmp);
		parts2VertexMu.push_back((*itmp));}
	}

    StatusCode sc = StatusCode::SUCCESS;
    LHCb::Vertex vtxTau;
    LHCb::Vertex vtxMu;
    LHCb::Vertex vtxTauDst;
    LHCb::Vertex vtxMuDst;
    sc = m_pVertexFit->fit (vtxMu,parts2VertexMu);
    debug() << "MU VERTEX FIT STATUS " << sc << endreq;;


    test &= tuple->column(prefix + "_DISCARDMu_CHI2", vtxMu.chi2() );
    test &= tuple->column(prefix + "_DISCARDMu_NDOF", vtxMu.nDoF() );

    const Gaudi::SymMatrix3x3 & Mum = vtxMu.covMatrix ();
    test &= tuple->column(prefix + "_DISCARDMu_", vtxMu.position() );
    test &= tuple->column(prefix + "_DISCARDMu_XERR", std::sqrt( Mum(0,0) ) );
    test &= tuple->column(prefix + "_DISCARDMu_YERR", std::sqrt( Mum(1,1) ) );
    test &= tuple->column(prefix + "_DISCARDMu_ZERR", std::sqrt( Mum(2,2) ) );


    double MuDlt, MuDltchi, MuDlterr;
    sc = m_ltfit->fit ( vtxMu, *D , MuDlt, MuDlterr, MuDltchi );
    test &= tuple->column(prefix + "_DISCARDMu_DTAU", MuDlt );
    test &= tuple->column(prefix + "_DISCARDMu_DTAUCHI2", MuDltchi );
    test &= tuple->column(prefix + "_DISCARDMu_DTAUERR", MuDlterr );

    double MuDmuDoca,MuDmuDocachi2;
    sc = m_dist->distance(muMu,D,MuDmuDoca,MuDmuDocachi2);
    test &= tuple->column(prefix + "_DISCARDMu_DMUDOCA", MuDmuDoca );

    double MupimuDoca,MupimuDocachi2;
    sc = m_dist->distance(muMu,pislow,MupimuDoca,MupimuDocachi2);
    test &= tuple->column(prefix + "_DISCARDMu_PIMUDOCA", MupimuDoca );
    
    
    debug() << "PAST FILL " << endreq;
    //}
    // replaced by V.B. 20.Aug.2k+9: (parts2Vertex,vtxWithExtraTrack);
    // Remove the added track from parts2Vertex

    

  return StatusCode(test);
}

//=========================================================================
//
//=========================================================================
const Vertex* TupleToolTagDiscardDstMu::originVertex( const Particle* top
                                               , const Particle* P ) const {
  if( top == P || P->isBasicParticle() ) return 0;

  const SmartRefVector< LHCb::Particle >& dau = top->daughters ();
  if( dau.empty() ){
    // if (msgLevel(MSG::DEBUG)) debug() << " Particle has no daughters! "  << endreq;
    return 0;
  }

  SmartRefVector< LHCb::Particle >::const_iterator it;
  for( it = dau.begin(); dau.end()!=it; ++it ){
    if( P == *it ){ // I found the daughter
      return top->endVertex();
    }
  }

  // vertex not yet found, get deeper in the decay:
  for( it = dau.begin(); dau.end()!=it; ++it ){
    if( P != *it && !(*it)->isBasicParticle() ){
      const Vertex* vv = originVertex( *it, P );
      if( vv ) return vv;
    }
  }
  return 0;
}
