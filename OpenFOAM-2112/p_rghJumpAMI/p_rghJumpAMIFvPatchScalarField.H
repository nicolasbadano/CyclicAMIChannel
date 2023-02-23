/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2012-2016 OpenFOAM Foundation
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::p_rghJumpAMIFvPatchScalarField

Group
    grpCoupledBoundaryConditions

Description
    This boundary condition provides a jump condition for p_rgh, using the \c cyclicAMI
    condition as a base.  The jump is specified as a time-varying uniform
    value across the patch.

Usage
    \table
        Property     | Description             | Required    | Default value
        patchType    | underlying patch type should be \c cyclicAMI| yes |
        jumpTable    | jump value              | yes         |
    \endtable

    Example of the boundary condition specification:
    \verbatim
    <patchName>
    {
        type            p_rghJumpAMI;
        patchType       cyclicAMI;
        jumpTable       constant 0.981;
    }
    \endverbatim

    The above example shows the use of a fixed jump of 9.81 m/s2 x 0.1 m.

Note
    The uniformValue entry is a Function1 type, able to describe time
    varying functions.  The example above gives the usage for supplying a
    constant value.

    The underlying \c patchType should be set to \c cyclic

See also
    Foam::jumpCyclicAMIFvPatchScalarField
    Foam::Function1Types

SourceFiles
    p_rghJumpAMIFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#ifndef p_rghJumpAMIFvPatchScalarField_H
#define p_rghJumpAMIFvPatchScalarField_H

#include "fixedJumpAMIFvPatchField.H"
#include "Function1.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                 Class p_rghJumpAMIFvPatchScalarField Declaration
\*---------------------------------------------------------------------------*/

class p_rghJumpAMIFvPatchScalarField
:
    public fixedJumpAMIFvPatchField<scalar>
{

protected:

    // Protected data

        //- "jump" table
        autoPtr<Function1<scalar>> jumpTable_;


public:

    //- Runtime type information
    TypeName("p_rghJumpAMI");

    // Constructors

        //- Construct from patch and internal field
        p_rghJumpAMIFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        p_rghJumpAMIFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given p_rghJumpAMIFvPatchScalarField onto a
        //  new patch
        p_rghJumpAMIFvPatchScalarField
        (
            const p_rghJumpAMIFvPatchScalarField&,
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy
        p_rghJumpAMIFvPatchScalarField
        (
            const p_rghJumpAMIFvPatchScalarField&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchScalarField> clone() const
        {
            return tmp<fvPatchScalarField>
            (
                new p_rghJumpAMIFvPatchScalarField(*this)
            );
        }

        //- Construct as copy setting internal field reference
        p_rghJumpAMIFvPatchScalarField
        (
            const p_rghJumpAMIFvPatchScalarField&,
            const DimensionedField<scalar, volMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual tmp<fvPatchScalarField> clone
        (
            const DimensionedField<scalar, volMesh>& iF
        ) const
        {
            return tmp<fvPatchScalarField>
            (
                new p_rghJumpAMIFvPatchScalarField(*this, iF)
            );
        }


    // Member functions

        //- Update the coefficients
        virtual void updateCoeffs();

        //- Write
        virtual void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
