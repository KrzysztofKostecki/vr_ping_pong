#pragma once
#include "RenderableInterface.h"
class Paddle :
	public VRCapable
{

public:
	Paddle(RenderInfo& renderInfo, VRInfo& vrInfo) :
		VRCapable{ renderInfo, vrInfo },
		m_shaderDesc(CompileGLShader(shaderName, vertexShaderContent, fragmentShaderContent)),
		m_matrixShaderLocation(GetShaderParamLocation(m_shaderDesc, "matrix")) 
	{

		vr::VRInput()->GetActionHandle("/actions/demo/out/Haptic_Left", &vrInfo.m_rHand[VRInfo::EHand::Left].m_actionHaptic);
		vr::VRInput()->GetInputSourceHandle("/user/hand/left", &vrInfo.m_rHand[VRInfo::EHand::Left].m_source);

		vr::VRInput()->GetActionHandle("/actions/demo/out/Haptic_Right", &vrInfo.m_rHand[VRInfo::EHand::Right].m_actionHaptic);
		vr::VRInput()->GetInputSourceHandle("/user/hand/right", &vrInfo.m_rHand[VRInfo::EHand::Right].m_source);
	}

	// Inherited via VRCapable
	void RenderScene(vr::Hmd_Eye nEye) override;

private:
	GLuint m_shaderDesc;
	GLuint m_matrixShaderLocation;
private:
	static constexpr const char* shaderName = "controller";
	static constexpr const char* vertexShaderContent =
		"#version 410\n"
		"uniform mat4 matrix;\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec3 v3ColorIn;\n"
		"out vec4 v4Color;\n"
		"void main()\n"
		"{\n"
		"	v4Color.xyz = v3ColorIn; v4Color.a = 1.0;\n"
		"	gl_Position = matrix * position;\n"
		"}\n";
	static constexpr const char* fragmentShaderContent =
		"#version 410\n"
		"in vec4 v4Color;\n"
		"out vec4 outputColor;\n"
		"void main()\n"
		"{\n"
		"   outputColor = v4Color;\n"
		"}\n";

};

