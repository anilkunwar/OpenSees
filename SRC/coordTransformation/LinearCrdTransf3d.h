/* ****************************************************************** **
**    OpenSees - Open System for Earthquake Engineering Simulation    **
**          Pacific Earthquake Engineering Research Center            **
**                                                                    **
**                                                                    **
** (C) Copyright 1999, The Regents of the University of California    **
** All Rights Reserved.                                               **
**                                                                    **
** Commercial use of this program without express permission of the   **
** University of California, Berkeley, is strictly prohibited.  See   **
** file 'COPYRIGHT'  in main directory for information on usage and   **
** redistribution,  and for a DISCLAIMER OF ALL WARRANTIES.           **
**                                                                    **
** Developed by:                                                      **
**   Frank McKenna (fmckenna@ce.berkeley.edu)                         **
**   Gregory L. Fenves (fenves@ce.berkeley.edu)                       **
**   Filip C. Filippou (filippou@ce.berkeley.edu)                     **
**                                                                    **
** ****************************************************************** */
                                                                        
// $Revision: 1.2 $
// $Date: 2001-06-05 06:01:09 $
// $Source: /usr/local/cvs/OpenSees/SRC/coordTransformation/LinearCrdTransf3d.h,v $
                                                                        
                                                                        
// File: ~/crdTransf/LinearCrdTransf3d.h
//
// Written: Remo Magalhaes de Souza (rmsouza@ce.berkeley.edu)
// Created: 04/2000
// Revision: A
//
// Description: This file contains the class definition for
// LinearCrdTransf3d.h. LinearCrdTransf3d provides the
// abstraction of a linear transformation for a spatial frame
// between the global and basic coordinate systems

// What: "@(#) LinearCrdTransf3d.h, revA"

#ifndef LinearCrdTransf3d_h
#define LinearCrdTransf3d_h

#include <CrdTransf3d.h>
#include <Vector.h>
#include <Matrix.h>

class LinearCrdTransf3d: public CrdTransf3d
{
  public:
    LinearCrdTransf3d (int tag, const Vector &vecInLocXZPlane);
    LinearCrdTransf3d (int tag, const Vector &vecInLocXZPlane,
		const Vector &rigJntOffsetI,
		const Vector &rigJntOffsetJ);
    
    LinearCrdTransf3d();
    ~LinearCrdTransf3d();

    int    initialize(Node *node1Pointer, Node *node2Pointer);
    int    update(void);
    double getInitialLength(void);
    double getDeformedLength(void);

    int commitState(void);
    int revertToLastCommit(void);        
    int revertToStart(void);
    
    const Vector &getBasicTrialDisp     (void);
    const Vector &getBasicIncrDisp      (void);
    const Vector &getBasicIncrDeltaDisp (void);

    const Vector &getGlobalResistingForce (const Vector &basicForce, const Vector &uniformLoad);
    const Matrix &getGlobalStiffMatrix    (const Matrix &basicStiff, const Vector &basicForce);

    CrdTransf3d *getCopy(void);
    
    int sendSelf(int cTag, Channel &theChannel);
    int recvSelf(int cTag, Channel &theChannel, FEM_ObjectBroker &theBroker);

    void Print(ostream &s, int flag =0);
  
    // functions used in post-processing only    
    const Vector &getPointGlobalCoordFromLocal (const Vector &localCoords);
    const Vector &getPointGlobalDisplFromBasic (double xi, const Vector &basicDisps);
  
  private:
    int  computeElemtLengthAndOrient (void);
    int  getLocalAxes (void);

    // internal data
    Node *nodeIPtr, 
	 *nodeJPtr;          // pointers to the element two endnodes

    double *nodeIOffset, *nodeJOffset;	// rigid joint offsets

    double R[3][3];	// Transformation matrix

    double L;                // undeformed element length
};

#endif

