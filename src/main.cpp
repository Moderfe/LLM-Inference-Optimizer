#include "llm_optimizer.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

int main() {
    std::cout << "LLM Inference Optimizer Example" << std::endl;

    // Example 1: Basic inference
    LLMOptimizer::Model model1 = LLMOptimizer::create_model("model_v1.bin");
    std::cout << model1.infer("What is the capital of France?") << std::endl;

    // Example 2: Inference with INT8 quantization
    LLMOptimizer::Model model2 = LLMOptimizer::create_model("model_v2.bin");
    model2.quantize(LLMOptimizer::QuantizationType::INT8);
    std::cout << model2.infer("Explain quantum computing.") << std::endl;

    // Example 3: Inference with INT4 quantization
    LLMOptimizer::Model model3 = LLMOptimizer::create_model("model_v3.bin");
    model3.quantize(LLMOptimizer::QuantizationType::INT4);
    std::cout << model3.infer("Summarize the latest AI research.") << std::endl;

    return 0;
}
