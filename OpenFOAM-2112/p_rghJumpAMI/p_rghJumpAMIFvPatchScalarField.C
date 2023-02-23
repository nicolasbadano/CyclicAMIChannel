/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2012-2017 OpenFOAM Foundation
    Copyright (C) 2021 OpenCFD Ltd.
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

\*---------------------------------------------------------------------------*/

#include "p_rghJumpAMIFvPatchScalarField.H"
#include "addToRunTimeSelectionTable.H"
#include "volFields.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::p_rghJumpAMIFvPatchScalarField::p_rghJumpAMIFvPatchScalarField
(
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF
)
:
    fixedJumpAMIFvPatchField<scalar>(p, iF),
    jumpTable_()
{}


Foam::p_rghJumpAMIFvPatchScalarField::p_rghJumpAMIFvPatchScalarField
(
    const p_rghJumpAMIFvPatchScalarField& ptf,
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    fixedJumpAMIFvPatchField<scalar>(ptf, p, iF, mapper),
    jumpTable_(ptf.jumpTable_.clone())
{}


Foam::p_rghJumpAMIFvPatchScalarField::p_rghJumpAMIFvPatchScalarField
(
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF,
    const dictionary& dict
)
:
    fixedJumpAMIFvPatchField<scalar>(p, iF),
    jumpTable_()
{
    if (this->cyclicAMIPatch().owner())
    {
        jumpTable_ = Function1<scalar>::New("jumpTable", dict, &this->db());
    }

    if (dict.found("value"))
    {
        fvPatchScalarField::operator=(scalarField("value", dict, p.size()));
    }
    else
    {
        this->evaluate(Pstream::commsTypes::blocking);
    }
}


Foam::p_rghJumpAMIFvPatchScalarField::p_rghJumpAMIFvPatchScalarField
(
    const p_rghJumpAMIFvPatchScalarField& ptf
)
:
    fixedJumpAMIFvPatchField<scalar>(ptf),
    jumpTable_(ptf.jumpTable_.clone())
{}


Foam::p_rghJumpAMIFvPatchScalarField::p_rghJumpAMIFvPatchScalarField
(
    const p_rghJumpAMIFvPatchScalarField& ptf,
    const DimensionedField<scalar, volMesh>& iF
)
:
    fixedJumpAMIFvPatchField<scalar>(ptf, iF),
    jumpTable_(ptf.jumpTable_.clone())
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::p_rghJumpAMIFvPatchScalarField::updateCoeffs()
{
    if (this->updated())
    {
        return;
    }

    if (this->cyclicAMIPatch().owner())
    {
        scalarField alphap = this->patch().lookupPatchField<volScalarField, scalar>("alpha.water");
        //this->jump_ = jumpGHTable_->value(this->db().time().value()); //* alphap;
        this->jump_ = jumpTable_->value(this->db().time().value()) * (1.0 + 999.0 * alphap);
    }

    fixedJumpAMIFvPatchField<scalar>::updateCoeffs();
}


void Foam::p_rghJumpAMIFvPatchScalarField::write(Ostream& os) const
{
    fixedJumpAMIFvPatchField<scalar>::write(os);
    if (this->cyclicAMIPatch().owner())
    {
        jumpTable_->writeData(os);
    }
}


// ************************************************************************* //

namespace Foam
{
   makePatchTypeField
   (
       fvPatchScalarField,
       p_rghJumpAMIFvPatchScalarField
   );
}


// ************************************************************************* //
