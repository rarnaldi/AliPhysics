/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// Modified version of AliAnalysisTaskCheckCascade.h
// Used bits of code from AliAnalysisTaskCheckPerformanceStrange
//
// --- David Dobrigkeit Chinellato
//
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

#ifndef AliAnalysisTaskStrangenessVsMultiplicity_H
#define AliAnalysisTaskStrangenessVsMultiplicity_H

class TList;
class TH1F;
class TH2F;
class TH3F;
class TVector3;
class THnSparse;

class AliESDpid;
class AliESDtrackCuts;
class AliAnalysisUtils;
class AliPPVsMultUtils;
class AliESDEvent;
class AliPhysicsSelection;
class AliCFContainer;

//#include "TString.h"
//#include "AliESDtrackCuts.h"
//#include "AliAnalysisTaskSE.h"

class AliAnalysisTaskStrangenessVsMultiplicity : public AliAnalysisTaskSE {
 public:
  AliAnalysisTaskStrangenessVsMultiplicity();
  AliAnalysisTaskStrangenessVsMultiplicity(const char *name);
  virtual ~AliAnalysisTaskStrangenessVsMultiplicity();
  
  virtual void   UserCreateOutputObjects();
  virtual void   UserExec(Option_t *option);
  virtual void   Terminate(Option_t *);
  Double_t MyRapidity(Double_t rE, Double_t rPz) const;

  void SetSaveV0s                (Bool_t lSaveV0s        = kTRUE ) { fkSaveV0Tree        = lSaveV0s;        }
  void SetSaveCascades           (Bool_t lSaveCascades   = kTRUE ) { fkSaveCascadeTree   = lSaveCascades;   }
  
//---------------------------------------------------------------------------------------
  //Task Configuration: Meant to enable quick re-execution of vertexer if needed
  void SetRunVertexers ( Bool_t lRunVertexers = kTRUE) { fkRunVertexers = lRunVertexers; }
//---------------------------------------------------------------------------------------
  //Task Configuration: Skip Event Selections after trigger (VZERO test) 
  void SetSkipEventSelection ( Bool_t lSkipEventSelection = kTRUE) { fkSkipEventSelection = lSkipEventSelection; }
//---------------------------------------------------------------------------------------
//Setters for the V0 Vertexer Parameters
  void SetV0VertexerMaxChisquare   ( Double_t lParameter ){ fV0VertexerSels[0] = lParameter; }
  void SetV0VertexerDCAFirstToPV   ( Double_t lParameter ){ fV0VertexerSels[1] = lParameter; }
  void SetV0VertexerDCASecondtoPV  ( Double_t lParameter ){ fV0VertexerSels[2] = lParameter; }
  void SetV0VertexerDCAV0Daughters ( Double_t lParameter ){ fV0VertexerSels[3] = lParameter; }
  void SetV0VertexerCosinePA       ( Double_t lParameter ){ fV0VertexerSels[4] = lParameter; }
  void SetV0VertexerMinRadius      ( Double_t lParameter ){ fV0VertexerSels[5] = lParameter; }
  void SetV0VertexerMaxRadius      ( Double_t lParameter ){ fV0VertexerSels[6] = lParameter; }
//---------------------------------------------------------------------------------------
//Setters for the Cascade Vertexer Parameters
  void SetCascVertexerMaxChisquare         ( Double_t lParameter ){ fCascadeVertexerSels[0] = lParameter; } 
  void SetCascVertexerMinV0ImpactParameter ( Double_t lParameter ){ fCascadeVertexerSels[1] = lParameter; } 
  void SetCascVertexerV0MassWindow         ( Double_t lParameter ){ fCascadeVertexerSels[2] = lParameter; } 
  void SetCascVertexerDCABachToPV          ( Double_t lParameter ){ fCascadeVertexerSels[3] = lParameter; } 
  void SetCascVertexerDCACascadeDaughters  ( Double_t lParameter ){ fCascadeVertexerSels[4] = lParameter; }
  void SetCascVertexerCascadeCosinePA      ( Double_t lParameter ){ fCascadeVertexerSels[5] = lParameter; }  
  void SetCascVertexerCascadeMinRadius     ( Double_t lParameter ){ fCascadeVertexerSels[6] = lParameter; }  
  void SetCascVertexerCascadeMaxRadius     ( Double_t lParameter ){ fCascadeVertexerSels[7] = lParameter; }  
//---------------------------------------------------------------------------------------
  
 private:
        // Note : In ROOT, "//!" means "do not stream the data from Master node to Worker node" ...
        // your data member object is created on the worker nodes and streaming is not needed.
        // http://root.cern.ch/download/doc/11InputOutput.pdf, page 14
  TList  *fListHist;  //! List of Cascade histograms
  TTree  *fTreeEvent;              //! Output Tree, Events
  TTree  *fTreeV0;              //! Output Tree, V0s
  TTree  *fTreeCascade;              //! Output Tree, Cascades

  AliPIDResponse *fPIDResponse;     // PID response object
  AliESDtrackCuts *fESDtrackCuts;   // ESD track cuts used for primary track definition
    AliPPVsMultUtils *fPPVsMultUtils; //

  //Objects Controlling Task Behaviour 
  Bool_t fkSaveV0Tree;              //if true, save TTree
  Bool_t fkSaveCascadeTree;         //if true, save TTree

  //Objects Controlling Task Behaviour: has to be streamed! 
  Bool_t    fkRunVertexers;           // if true, re-run vertexer with loose cuts *** only for CASCADES! *** 
  Bool_t    fkSkipEventSelection;     // if true, will only perform TRIGGER selection (currently kMB, to change) 
  Double_t  fV0VertexerSels[7];        // Array to store the 7 values for the different selections V0 related
  Double_t  fCascadeVertexerSels[8];   // Array to store the 8 values for the different selections Casc. related

//===========================================================================================
//   Variables for Event Tree
//===========================================================================================
  Float_t fAmplitude_V0A;   //!
  Float_t fAmplitude_V0C;   //! 
  Float_t fAmplitude_V0AEq; //!
  Float_t fAmplitude_V0CEq; //! 
  Float_t fCentrality_V0A;         //! 
  Float_t fCentrality_V0C;         //! 
  Float_t fCentrality_V0M;         //! 
  Float_t fCentrality_V0AEq;       //! 
  Float_t fCentrality_V0CEq;       //! 
  Float_t fCentrality_V0MEq;       //!
  Float_t fCustomCentrality_V0M; //!
  Float_t fCustomCentrality_V0MEq; //!
  Int_t fRefMultEta5;              //!
  Int_t fRefMultEta8;              //!   
  Int_t fRunNumber;                //!
    
    //Event Characterization Variables - optional
    Bool_t fEvSel_HasAtLeastSPDVertex;      //!
    Bool_t fEvSel_VtxZCut;                  //!
    Bool_t fEvSel_IsNotPileup;              //!
    Bool_t fEvSel_IsNotPileupInMultBins;    //!
    Bool_t fEvSel_HasVtxContributor;        //!
    
    //Other Selections: more dedicated filtering to be studied!
    Int_t fEvSel_nTracklets;              //!
    Int_t fEvSel_nSPDClusters;            //!
    

//===========================================================================================
//   Variables for V0 Tree
//===========================================================================================
	Float_t fTreeVariableChi2V0;         //!
	Float_t fTreeVariableDcaV0Daughters; //!
	Float_t fTreeVariableDcaV0ToPrimVertex; //!
	Float_t fTreeVariableDcaPosToPrimVertex; //!
	Float_t fTreeVariableDcaNegToPrimVertex; //!
	Float_t fTreeVariableV0CosineOfPointingAngle; //!
	Float_t fTreeVariableV0Radius; //!
	Float_t fTreeVariablePt; //!
	Float_t fTreeVariableRapK0Short; //!
	Float_t fTreeVariableRapLambda; //!
	Float_t fTreeVariableInvMassK0s; //!
	Float_t fTreeVariableInvMassLambda; //!
	Float_t fTreeVariableInvMassAntiLambda; //!
	Float_t fTreeVariableAlphaV0; //!
	Float_t fTreeVariablePtArmV0;//!
	Float_t fTreeVariableNegEta; //!
	Float_t fTreeVariablePosEta; //!

	Float_t fTreeVariableNSigmasPosProton; //!
	Float_t fTreeVariableNSigmasPosPion; //! 
	Float_t fTreeVariableNSigmasNegProton; //!
	Float_t fTreeVariableNSigmasNegPion; //! 
	
	Float_t fTreeVariableDistOverTotMom;//!
	Int_t   fTreeVariableLeastNbrCrossedRows;//!
	Float_t fTreeVariableLeastRatioCrossedRowsOverFindable;//!

  //Event Multiplicity Variables 
  Float_t fTreeVariableCentV0A;    //!
  Float_t fTreeVariableCentV0C;    //!
  Float_t fTreeVariableCentV0M;    //!
  Float_t fTreeVariableCentV0AEq;  //!
  Float_t fTreeVariableCentV0CEq;  //!
  Float_t fTreeVariableCentV0MEq;  //!
  Float_t fTreeVariableAmpV0A;     //!
  Float_t fTreeVariableAmpV0C;     //!
  Float_t fTreeVariableAmpV0AEq;   //!
  Float_t fTreeVariableAmpV0CEq;   //!
  Int_t   fTreeVariableRefMultEta8;  //!
  Int_t   fTreeVariableRefMultEta5;  //!
  Int_t   fTreeVariableRunNumber; //! //want to re-quantile per run? here's your ticket

//===========================================================================================
//   Variables for Cascade Candidate Tree
//===========================================================================================
  Int_t fTreeCascVarCharge;         //! 
  Float_t fTreeCascVarMassAsXi;     //! 
  Float_t fTreeCascVarMassAsOmega;  //! 
  Float_t fTreeCascVarPt;           //!
  Float_t fTreeCascVarRapXi;        //!
  Float_t fTreeCascVarRapOmega;     //!
  Float_t fTreeCascVarNegEta;       //!
  Float_t fTreeCascVarPosEta;       //!
  Float_t fTreeCascVarBachEta;      //!
  Float_t fTreeCascVarDCACascDaughters; //!
  Float_t fTreeCascVarDCABachToPrimVtx; //!
  Float_t fTreeCascVarDCAV0Daughters;   //!
  Float_t fTreeCascVarDCAV0ToPrimVtx;   //!
  Float_t fTreeCascVarDCAPosToPrimVtx;  //!
  Float_t fTreeCascVarDCANegToPrimVtx;  //!
  Float_t fTreeCascVarCascCosPointingAngle;         //!
  Float_t fTreeCascVarCascRadius;                   //!
  Float_t fTreeCascVarV0Mass;                       //!
  Float_t fTreeCascVarV0CosPointingAngle;           //!
  Float_t fTreeCascVarV0CosPointingAngleSpecial;    //!
  Float_t fTreeCascVarV0Radius;                     //!
  Int_t   fTreeCascVarLeastNbrClusters;             //!
  Float_t fTreeCascVarDistOverTotMom;               //!

  //TPC dEdx 
  Float_t fTreeCascVarNegNSigmaPion;   //!
  Float_t fTreeCascVarNegNSigmaProton; //!
  Float_t fTreeCascVarPosNSigmaPion;   //! 
  Float_t fTreeCascVarPosNSigmaProton; //! 
  Float_t fTreeCascVarBachNSigmaPion;  //! 
  Float_t fTreeCascVarBachNSigmaKaon;  //! 

  //Event Multiplicity Variables 
  Float_t fTreeCascVarCentV0A;    //!
  Float_t fTreeCascVarCentV0C;    //!
  Float_t fTreeCascVarCentV0M;    //!
  Float_t fTreeCascVarCentV0AEq;  //!
  Float_t fTreeCascVarCentV0CEq;  //!
  Float_t fTreeCascVarCentV0MEq;  //!
  Float_t fTreeCascVarAmpV0A;     //!
  Float_t fTreeCascVarAmpV0C;     //!
  Float_t fTreeCascVarAmpV0AEq;   //!
  Float_t fTreeCascVarAmpV0CEq;   //!
  Int_t fTreeCascVarRefMultEta8;  //!
  Int_t fTreeCascVarRefMultEta5;  //!
  Int_t fTreeCascVarRunNumber;    //! //want to re-quantile per run? here's your ticket
  
//===========================================================================================
//   Histograms
//===========================================================================================

  TH1D *fHistEventCounter; //! 

   AliAnalysisTaskStrangenessVsMultiplicity(const AliAnalysisTaskStrangenessVsMultiplicity&);            // not implemented
   AliAnalysisTaskStrangenessVsMultiplicity& operator=(const AliAnalysisTaskStrangenessVsMultiplicity&); // not implemented
   
   ClassDef(AliAnalysisTaskStrangenessVsMultiplicity, 11);
};

#endif
