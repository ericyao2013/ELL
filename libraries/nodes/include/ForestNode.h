////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Machine Learning Library (EMLL)
//  File:     ForestNode.h (nodes)
//  Authors:  Ofer Dekel
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// model
#include "Node.h"
#include "ModelGraph.h"
#include "ModelTransformer.h"

// predictors
#include "ForestPredictor.h"
#include "SingleElementThresholdPredictor.h"
#include "ConstantNode.h"

// stl
#include <string>

namespace nodes
{
    /// <summary> Implements a forest node, which wraps the forest predictor. </summary>
    ///
    /// <typeparam name="SplitRuleType"> The split rule type. </typeparam>
    /// <typeparam name="EdgePredictorType"> The edge predictor type. </typeparam>
    template<typename SplitRuleType, typename EdgePredictorType>
    class ForestNode : public model::Node
    {
    public:
        /// @name Input and Output Ports
        /// @{
        static constexpr const char* inputPortName = "input";
        static constexpr const char* outputPortName = "output";
        static constexpr const char* treeOutputsPortName = "treeOutputs";
        static constexpr const char* edgeIndicatorVectorPortName = "edgeIndicatorVector";
        const model::OutputPort<double>& output = _output;
        const model::OutputPort<double>& treeOutputs = _treeOutputs;
        const model::OutputPort<bool>& edgeIndicatorVector = _edgeIndicatorVector;
        /// @}

        /// <summary> Constructor </summary>
        ///
        /// <param name="input"> The predictor's input. </param>
        /// <param name="forest"> The forest predictor. </param>
        ForestNode(const model::OutputPortElements<double>& input, const predictors::ForestPredictor<SplitRuleType, EdgePredictorType>& forest);
        
        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        static std::string GetTypeName() { return utilities::GetCompositeTypeName<SplitRuleType, EdgePredictorType>("ForestNode"); }

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        virtual std::string GetRuntimeTypeName() const override { return GetTypeName(); }

        /// <summary> Makes a copy of this node in the graph being constructed by the transformer. </summary>
        ///
        /// <param name="transformer"> [in,out] The transformer. </param>
        virtual void Copy(model::ModelTransformer& transformer) const override;

        /// <summary> Refines this node in the graph being constructed by the transformer </summary>
        virtual void Refine(model::ModelTransformer& transformer) const;

    protected:
        virtual void Compute() const override;

    private:
        // Input
        model::InputPort<double> _input;

        // Outputs
        model::OutputPort<double> _output;
        model::OutputPort<double> _treeOutputs;
        model::OutputPort<bool> _edgeIndicatorVector;

        // Forest
        predictors::ForestPredictor<SplitRuleType, EdgePredictorType> _forest;
    };

    /// <summary> Defines an alias representing a simple forest node, which holds a forest with a SingleElementThresholdPredictor as the split rule and ConstantPredictors on the edges. </summary>
    typedef ForestNode<predictors::SingleElementThresholdPredictor, predictors::ConstantPredictor>  SimpleForestNode;
}

#include "../tcc/ForestNode.tcc"
