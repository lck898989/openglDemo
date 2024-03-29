#ifndef SHADER_H
#define SHADER_H
#include <string>
using namespace std;
class Shader
{
public:
	unsigned int ID;
	// constructor generates the shader on the fly
	// ------------------------------------------------------------------------
	Shader(const char* vertexPath, const char* fragmentPath);
	// activate the shader
	// ------------------------------------------------------------------------
	void use();
	// utility uniform functions
	// -----------------------------------------------------
	void setBool(const string &name, bool value) const;
	void setInt(const string &name, int value) const;
	void setFloat(const string &name, float value) const;

private:
	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void checkCompileErrors(unsigned int shader, string type);
};
#endif