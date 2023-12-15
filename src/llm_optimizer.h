#ifndef LLM_OPTIMIZER_H
#define LLM_OPTIMIZER_H

#include <string>
#include <vector>
#include <memory>

namespace LLMOptimizer {

// Enum for different quantization types
enum class QuantizationType {
    NONE,
    INT8,
    INT4
};

// Abstract base class for an LLM inference backend
class IInferenceBackend {
public:
    virtual ~IInferenceBackend() = default;
    virtual void load_model(const std::string& model_path) = 0;
    virtual void apply_quantization(QuantizationType type) = 0;
    virtual std::string infer(const std::string& prompt) = 0;
};

// Model class that uses an inference backend
class Model {
public:
    // Constructor takes a unique_ptr to an IInferenceBackend implementation
    explicit Model(std::unique_ptr<IInferenceBackend> backend);

    // Loads the model using the backend
    void load(const std::string& model_path);

    // Applies quantization using the backend
    void quantize(QuantizationType type);

    // Performs inference using the backend
    std::string infer(const std::string& prompt);

private:
    std::unique_ptr<IInferenceBackend> backend_;
};

// Factory function to create a Model with a default backend
Model create_model(const std::string& model_path);

} // namespace LLMOptimizer

#endif // LLM_OPTIMIZER_H
