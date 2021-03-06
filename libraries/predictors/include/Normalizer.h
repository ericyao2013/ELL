////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     Normalizer.h (predictors)
//  Authors:  Ofer Dekel
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <data/include/IndexValue.h>

namespace ell
{
namespace predictors
{
    /// <summary> Applies an elementwise transformation to DataVectors. </summary>
    ///
    /// <typeparam name="policy"> Iteration policy (all, skipZeros). </typeparam>
    /// <typeparam name="TransformationType"> The transformation type. </typeparam>
    template <data::IterationPolicy policy, typename TransformationType>
    class Normalizer
    {
    public:
        /// <summary> Constructs an instance of Normalizer. </summary>
        ///
        /// <param name="transformation"> The transformation to apply to datavectors. </param>
        Normalizer(TransformationType transformation);

        /// <summary> Applies the normalizer to a new input. </summary>
        ///
        /// <typeparam name="OutputDataVectorType"> Output DataVector type. </typeparam>
        /// <typeparam name="InputDataVectorType"> Input DataVector type. </typeparam>
        /// <param name="input"> The input DataVector. </param>
        ///
        /// <returns> The output DataVector. </returns>
        template <typename OutputDataVectorType, typename InputDataVectorType>
        OutputDataVectorType Compute(const InputDataVectorType& input) const;

    private:
        TransformationType _transformation;
    };

    template <data::IterationPolicy policy, typename TransformationType>
    Normalizer<policy, TransformationType> MakeTransformationNormalizer(TransformationType transformation);
} // namespace predictors
} // namespace ell

#pragma region implementation

namespace ell
{
namespace predictors
{
    template <data::IterationPolicy policy, typename TransformationType>
    inline Normalizer<policy, TransformationType>::Normalizer(TransformationType transformation) :
        _transformation(transformation)
    {
    }

    template <data::IterationPolicy policy, typename TransformationType>
    template <typename OutputDataVectorType, typename InputDataVectorType>
    OutputDataVectorType Normalizer<policy, TransformationType>::Compute(const InputDataVectorType& input) const
    {
        return data::TransformAs<InputDataVectorType, policy, OutputDataVectorType>(input, _transformation);
    }

    template <data::IterationPolicy policy, typename TransformationType>
    Normalizer<policy, TransformationType> MakeTransformationNormalizer(TransformationType transformation)
    {
        return Normalizer<policy, TransformationType>(transformation);
    }
} // namespace predictors
} // namespace ell

#pragma endregion implementation
