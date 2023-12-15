#include "llm_optimizer.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>

namespace LLMOptimizer {

// Concrete implementation of IInferenceBackend for demonstration
class DummyInferenceBackend : public IInferenceBackend {
public:
    void load_model(const std::string& model_path) override {
        std::cout << "[DummyBackend] Loading model from: " << model_path << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "[DummyBackend] Model loaded successfully." << std::endl;
    }

    void apply_quantization(QuantizationType type) override {
        current_quantization_ = type;
        std::cout << "[DummyBackend] Applying " << (type == QuantizationType::INT8 ? "INT8" : (type == QuantizationType::INT4 ? "INT4" : "NONE")) << " quantization." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    std::string infer(const std::string& prompt) override {
        std::cout << "[DummyBackend] Processing prompt: \"" << prompt << "\"" << std::endl;
        int inference_time_ms = 1000;
        if (current_quantization_ == QuantizationType::INT8) inference_time_ms = 500;
        if (current_quantization_ == QuantizationType::INT4) inference_time_ms = 300;

        std::this_thread::sleep_for(std::chrono::milliseconds(inference_time_ms));

        std::vector<std::string> responses = {
            "The answer is a result of complex computations.",
            "My analysis indicates a high probability of...",
            "This query requires further deep learning inference.",
            "Generating a response based on optimized model parameters.",
            "The LLM provides the following insight:"
        };
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, responses.size() - 1);
        return responses[distrib(gen)] + " (Quant: " + std::to_string(static_cast<int>(current_quantization_)) + ").";
    }

private:
    QuantizationType current_quantization_ = QuantizationType::NONE;
};

// Model class implementation
Model::Model(std::unique_ptr<IInferenceBackend> backend) : backend_(std::move(backend)) {}

void Model::load(const std::string& model_path) {
    backend_->load_model(model_path);
}

void Model::quantize(QuantizationType type) {
    backend_->apply_quantization(type);
}

std::string Model::infer(const std::string& prompt) {
    return backend_->infer(prompt);
}

// Factory function implementation
Model create_model(const std::string& model_path) {
    auto backend = std::make_unique<DummyInferenceBackend>();
    backend->load_model(model_path);
    return Model(std::move(backend));
}

} // namespace LLMOptimizer
