//
// Created by human on 21.02.2021.
//

#include "Algorithm/Fc_ProducerConsumer.h"
#include "FcTrueTypeGL.h"
#include "TrueTypeGlyph.h"
#include <malloc.h>
#include <float.h>

const char m_truetype_vertexShader[] = "#version 430\n"
"in vec2 vPosition;"
"in vec2 vColor;"
"uniform vec2 vWindow;"
"//uniform vec2 vMouse;\n"
"uniform mat4 MVP;"
"uniform vec2 vSelector;"
"out vec2 fColor;"
"out vec2 fWindow;"
"out vec2 fMouse;"
"out vec2 fSelector;"
"void main(){"
"fColor = vColor;\n"
"fWindow = vWindow;\n"
"//fMouse = vMouse;\n"
"fSelector = vSelector;"
"if (vSelector.x == 0.0)\n"
"gl_Position = vec4(vPosition, 0, 1) * MVP;"
"else\n"
"gl_Position = vec4(vPosition, 0, 1);\n"
"}";

const char m_truetype_vertexShaderTest[] = "#version 430\n"
"in vec2 vPosition;"
"in vec2 vColor;"
"uniform mat3 vCurveTransform;\n"
"uniform mat4 vCurve;"
"uniform vec2 vWindow;"
"uniform vec2 vMouse;"
"uniform mat4 MVP;"
"uniform vec2 vSelector;"
"out mat3 fCurveTransform;\n"
"out mat4 fCurve;"
"out vec2 fColor;"
"out vec2 fWindow;"
"out vec2 fMouse;"
"out vec2 fSelector;"
"void main(){"
"fCurveTransform = vCurveTransform;"
"fCurve = vCurve;"
"fColor = vColor;"
"fWindow = vWindow;"
"fMouse = vMouse;"
"fSelector = vSelector;"
"gl_Position = vec4(vPosition, 0, 1);"
"}";

const char m_truetype_fragmentShaderTest[] = "#version 430\n"
"#define FLT_MAX 3.402823466e+38\n"
"in mat3 fCurveTransform;\n"
"in mat4 fCurve;\n"
"in vec2 fColor;\n"
"in vec2 fWindow;\n"
"in vec2 fMouse;\n"
"in vec2 fSelector;\n"
"uniform sampler1D  textureID;\n"
"uniform sampler1D  textureIDCurve;\n"
"vec4 curve(vec2 v0, vec2 v1, vec2 v2, vec2 v3){"
"       vec4 color = vec4(0);"
"       vec2 a = v3 - 2 * v2 + v1;\n"
"       vec2 b = 2 * (v2 - v1);\n"
"       vec2 d = b * b - 4 * a * (v1 - v0);\n"
"       vec4 d_sqrt = vec4(1, -1, 1, -1) * vec4(vec2(sqrt(d.x)), vec2(sqrt(d.y)));\n"
"       vec4 t = (d_sqrt - vec4(b.x, b.x, b.y, b.y)) / (2 * vec4(a.x, a.x, a.y, a.y));\n"
"       vec4 p = vec4(v1.y, v1.y, v1.x, v1.x) + t * vec4(b.y, b.y, b.x, b.x) + t * t * vec4(a.y, a.y, a.x, a.x);\n"
"       vec4 r = vec4(v0.y, v0.y, v0.x, v0.x) - p;"
"       t = step(vec4(-1.175494351e-38F), -abs(t - 0.5) + 0.5);"
"       r = step(vec4(0.00f), -abs(r) + 0.01);\n"
"       r = r * t;"
"       color += vec4(r.x+r.y+r.z+r.w) * vec4(0.0, 1.0, 0.0, 1.0);\n"
"       return color;"
"}"

"void main(){"
"vec2 scale = vec2(1.0) / fWindow;"
"vec2 xy = gl_FragCoord.xy * scale;"
"float step = (0.5 / fSelector.y);"
"vec3 first = fCurveTransform * vec3(fCurve[0].xy, 1);"
"vec3 second = fCurveTransform * vec3(fCurve[1].xy, 1);"
"vec3 third = fCurveTransform * vec3(fCurve[2].xy, 1);"
"vec4 color = curve(xy, first.xy, second.xy, third.xy);\n"
"if (length(first.xy - xy) < 0.01)"
"color = vec4(0, 0, 1, 1);"
"if (length(second.xy - xy) < 0.01)"
"color = vec4(1, 0, 0, 1);"
"if (length(third.xy - xy) < 0.01)"
"color = vec4(0, 0, 1, 1);"
"gl_FragColor = color;"
"}";

const char m_truetype_fragmentShader[] = "#version 430\n"
"#define FLT_MAX 3.402823466e+38F\n"
"#define FLT_MIN 1.175494351e-38F\n"
"#define M_PI 3.1415926535897932384626433832795\n"
"in vec2 fColor;\n"
"in vec2 fWindow;\n"
"in vec2 fMouse;\n"
"in vec2 fSelector;\n"
"uniform sampler1D  textureID;\n"
"uniform sampler1D  textureIDCurve;\n"

"vec4 curve(vec4 color, vec2 v0, vec2 v1, vec2 v2, vec2 v3, vec2 scale){"
"       //vec4 color = vec4(0);\n"
"       if (any(lessThan(abs(v3 - 2 * v2 + v1), scale)))"
"           v2 = v3;"
"       vec2 a = v3 - 2 * v2 + v1;\n"
"       vec2 b = 2 * (v2 - v1);\n"
"       vec2 d = b * b - 4 * a * (v1 - v0);\n"
"       vec4 d_sqrt = vec4(1, -1, 1, -1) * vec4(vec2(sqrt(d.x)), vec2(sqrt(d.y)));\n"
"       vec4 t = (d_sqrt - vec4(b.x, b.x, b.y, b.y)) / (2 * vec4(a.x, a.x, a.y, a.y));\n"
"       vec4 p = vec4(v1.y, v1.y, v1.x, v1.x) + t * vec4(b.y, b.y, b.x, b.x) + t * t * vec4(a.y, a.y, a.x, a.x);\n"
"       vec4 r = vec4(v0.y, v0.y, v0.x, v0.x) - p;"
"       t = step(vec4(0.0f), -abs(t - 0.5) + 0.5 + FLT_MIN);\n"
"       r = step(vec4(0.0f), -abs(r) + vec4(scale.x, scale.x, scale.y, scale.y));\n"
"       //r = smoothstep(vec4(0.0f), vec4(1.0f),  sqrt(0.001f / abs(r)));\n"
"       r = r * t;"
"       if (color.y < (vec4(r.x+r.y+r.z+r.w) * vec4(0.0, 1.0, 0.0, 1.0)).y)"
"       color = vec4(r.x+r.y+r.z+r.w) * vec4(0.0, 1.0, 0.0, 1.0);\n"
"       return color;"
"}"

"vec4 curve2(vec4 color, vec2 v0, vec2 v1, vec2 v2, vec2 v3, vec2 scale){"
"       if (any(lessThan(abs(v3 - 2 * v2 + v1), scale)))"
"           v2 = v3;"
"       vec2 a = v3 - 2 * v2 + v1;\n"
"       vec2 b = 2 * (v2 - v1);\n"
"       vec2 d = b * b - 4 * a * (v1 - v0);\n"
"       vec2 d_sqrt = vec2(1, -1) * vec2(sqrt(d.y));\n"
"       vec2 t = (d_sqrt - vec2(b.y)) / (2 * vec2(a.y));\n"
"       vec2 p = vec2(v1.x) + t * vec2(b.x) + t * t * vec2(a.x);\n"
"       vec2 line = step(vec2(0.0f), -abs(t - 0.5) + 0.5 + FLT_MIN);\n"
"       vec2 dist = (vec2(v0.x) - p) * line;"
"       if (dist.x + dist.y < 0.0f)\n"
"           color.y = color.y > 0.5f ? 0.5f : 1.0f;\n"
"       return color;"
"}"

"vec4 line(vec2 v0, vec2 v1, vec2 v2, vec2 scale) {\n"
"   vec4 color = vec4(0);\n"
"   vec2 v3 = v2 - v1;\n"
"   vec2 v4 = v0 - v1;\n"
"   float s0 = v3.x * v4.y;\n"
"   float s1 = v4.x * v3.y;\n"
"   v3 = v0 - v2;\n"
"   v4 = v0 - v1;\n"
"   float s2 = v3.x * v4.x;\n"
"   float s3 = v3.y * v4.y;\n"
"   vec2 v = vec2(s0 - s1, s2 + s3);\n"
"   v = step(vec2(0.0f), vec2(-abs(v.x) + scale.x, -v.y + FLT_MIN));"
"   color += vec4(v.x * v.y) * vec4(0.0, 1.0, 0.0, 1.0);"
"   return color;\n"
"}\n"

"vec4 grid(vec2 xy, vec2 step, vec2 scale){"
"		vec2 value = fract(xy / step);\n"
"		value.x = value.x <= 1.0 / step.x ? 1 : 0;\n"
"		value.y = value.y <= 1.0 / step.y ? 1 : 0;\n"
"		float result = value.x + value.y;\n"
"       return vec4(result);\n"
"}"

"void main(){"
"vec2 scale = vec2(1.0) / fWindow;"
"vec2 xy = gl_FragCoord.xy * scale;"
"float step = (0.5 / fSelector.y);"

"vec4 color = vec4(fColor, 0.1, 1);"
"if (fSelector.x > 0.0){"
"color = vec4(0.5, 0.0, 0.5, 1);"
"for (float i = 0; i < fSelector.x; i++){"
"vec4 points = texture(textureID,  step + i / fSelector.y );"
"vec4 curveData = texture(textureIDCurve,  step + i / fSelector.y );"

"if (curveData.w * curveData.z > 0.5){\n"
"//color += line(xy, points.xy, points.zw, scale);\n"
"color = curve2(color, xy, points.zw, points.xy, points.xy, scale);\n"
"}else if(curveData.z < 0.5){\n"
"color = curve2(color, xy, points.zw, points.xy, curveData.xy, scale);\n"
"}\n"
"}}\n"
"color += grid(gl_FragCoord.xy, vec2(50., 50.), fWindow);\n"
"gl_FragColor = color;"
"}";

void FcTrueTypeGL_resizeViewport(float width, float height) {
	glViewport(0, 0, width, height);
};
void FcTrueTypeGL_copyDataArray(void* data0) {
	struct _FcTrueTypeGL_t* m_truetype = data0;

	float* m_ptr;
	uint16_t x, i, j, t;
	double m_maxX = DBL_MIN;
	double m_maxY = DBL_MIN;
	double m_minX = DBL_MAX;
	double m_minY = DBL_MAX;
	//m_truetype->m_glyph->number_points = 84;

	glBindTexture(GL_TEXTURE_1D, m_truetype->m_textureBuffers[0]);
	m_ptr = (float*)calloc(1, 4 * m_truetype->m_glyph->number_points * sizeof(float));
	for (i = 0; i < m_truetype->m_glyph->number_points; i++) {
		m_maxX = m_truetype->m_glyph->parameters[i].x > m_maxX ? m_truetype->m_glyph->parameters[i].x : m_maxX;
		m_minX = m_truetype->m_glyph->parameters[i].x < m_minX ? m_truetype->m_glyph->parameters[i].x : m_minX;
		m_maxY = m_truetype->m_glyph->parameters[i].y > m_maxY ? m_truetype->m_glyph->parameters[i].y : m_maxY;
		m_minY = m_truetype->m_glyph->parameters[i].y < m_minY ? m_truetype->m_glyph->parameters[i].y : m_minY;
	}
	for (i = 0, x = 0; i < m_truetype->m_glyph->number_contours; i++) {
		for (j = m_truetype->m_glyph->endCountours[i]; x <= m_truetype->m_glyph->endCountours[i]; j = x, x++) {
			m_ptr[4 * x + 0] = (1.0 + ((double)m_truetype->m_glyph->parameters[x].x * (2.0 / (m_maxX - m_minX)) - ((m_maxX + m_minX) / (m_maxX - m_minX)))) / 2.0;
			m_ptr[4 * x + 1] = (1.0 + ((double)m_truetype->m_glyph->parameters[x].y * (2.0 / (m_maxY - m_minY)) - ((m_maxY + m_minY) / (m_maxY - m_minY)))) / 2.0;
			m_ptr[4 * x + 2] = (1.0 + ((double)m_truetype->m_glyph->parameters[j].x * (2.0 / (m_maxX - m_minX)) - ((m_maxX + m_minX) / (m_maxX - m_minX)))) / 2.0;
			m_ptr[4 * x + 3] = (1.0 + ((double)m_truetype->m_glyph->parameters[j].y * (2.0 / (m_maxY - m_minY)) - ((m_maxY + m_minY) / (m_maxY - m_minY)))) / 2.0;
			//printf("m_ptr[%d]=%f, m_ptr[%d]=%f, m_ptr[%d]=%f, m_ptr[%d]=%f;\n", 4 * x + 0,
			//       m_ptr[4 * x + 0], 4 * x + 1, m_ptr[4 * x + 1], 4 * x + 2, m_ptr[4 * x + 2], 4 * x + 3, m_ptr[4 * x + 3]);
		}
	}
	glTexSubImage1D(GL_TEXTURE_1D, 0, 0, m_truetype->m_glyph->number_points, GL_RGBA, GL_FLOAT, m_ptr);

	glBindTexture(GL_TEXTURE_1D, m_truetype->m_textureBuffers[1]);
	for (i = 0, x = 0; i < m_truetype->m_glyph->number_contours; i++) {
		for (j = m_truetype->m_glyph->endCountours[i]; x <= m_truetype->m_glyph->endCountours[i]; j = x, x++) {
			if (x + 1 > m_truetype->m_glyph->endCountours[i])
				t = i == 0 ? 0 : m_truetype->m_glyph->endCountours[i - 1] + 1;
			else
				t = x + 1;
			m_ptr[4 * x + 0] = (1.0 + ((double)m_truetype->m_glyph->parameters[t].x * (2.0 / (m_maxX - m_minX)) - ((m_maxX + m_minX) / (m_maxX - m_minX)))) / 2.0;
			m_ptr[4 * x + 1] = (1.0 + ((double)m_truetype->m_glyph->parameters[t].y * (2.0 / (m_maxY - m_minY)) - ((m_maxY + m_minY) / (m_maxY - m_minY)))) / 2.0;
			m_ptr[4 * x + 2] = m_truetype->m_glyph->m_flags[x] & 1;
			m_ptr[4 * x + 3] = m_truetype->m_glyph->m_flags[j] & 1;
			//printf("m_ptr[%d]=%f, m_ptr[%d]=%f, m_ptr[%d]=%f, m_ptr[%d]=%f;\n", 4 * x + 0,
			//       m_ptr[4 * x + 0], 4 * x + 1, m_ptr[4 * x + 1], 4 * x + 2, m_ptr[4 * x + 2], 4 * x + 3, m_ptr[4 * x + 3]);
		}
	}

	glTexSubImage1D(GL_TEXTURE_1D, 0, 0, m_truetype->m_glyph->number_points, GL_RGBA, GL_FLOAT, m_ptr);
	glBindTexture(GL_TEXTURE_1D, 0);

	for (i = 0; i < m_truetype->m_glyph->number_points; i++) {
		m_ptr[2 * i + 0] = m_truetype->m_glyph->parameters[i].x;
		m_ptr[2 * i + 1] = m_truetype->m_glyph->parameters[i].y;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_truetype->m_vertexBuffers[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_truetype->m_glyph->number_points * 2 * sizeof(*m_ptr), m_ptr);

	glBindBuffer(GL_ARRAY_BUFFER, m_truetype->m_vertexColor);
	for (i = 0, x = 0; i < m_truetype->m_glyph->number_contours; i++) {
		for (; x <= m_truetype->m_glyph->endCountours[i]; x++) {
			m_ptr[2 * x + 0] = m_truetype->m_glyph->m_flags[x] & 1;
			m_ptr[2 * x + 1] = (float)(m_truetype->m_glyph->m_flags[x] & 1) / (x + 1);
		}
	}
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_truetype->m_glyph->number_points * 2 * sizeof(float), m_ptr);
	printf("%d %f %f\n", m_truetype->m_unicode, m_maxY, m_minY);
	free(m_ptr);
};
void FcTrueTypeGL_testVectors(struct _FcTrueTypeGL_t* m_truetype) {
	uint16_t i, j;
	//FcMatrix4x4f_fprintp(m_truetype->m_MVP, 4, 6);
	for (i = 0, j = 0; i < m_truetype->m_glyph->number_contours; i++) {
		for (; j <= m_truetype->m_glyph->endCountours[i]; j++) {
			FcVec4_t m_vec = FcVec4(m_truetype->m_glyph->parameters[j].x, m_truetype->m_glyph->parameters[j].y, 0, 1);
			FcVec4_t m_res = FcMatrix4x4_multiply_mv(m_truetype->m_MVP, m_vec);
			if (m_res.m[0] < -1.0 || m_res.m[0] > 1.0 || m_res.m[1] < -1.0 || m_res.m[1] > 1.0)
				fprintf(stderr, "%f %f %f %f\n", m_vec.m[0], m_vec.m[1], m_res.m[0], m_res.m[1]);
			else
				fprintf(stdout, "%f %f %f %f\n", m_vec.m[0], m_vec.m[1], m_res.m[0], m_res.m[1]);
		}
	}
}

void FcTrueTypeGL_window(unsigned int width, unsigned int height, void* data0, void* data1) {
	struct _FcTrueTypeGL_t* m_truetype = data0;
	Fc_ProducerConsumerData_t init;
	init.id = e_FcGL_callFunction_fff;
	init.s0.v = FcTrueTypeGL_resizeViewport;
	init.s1.f = (float)width;
	init.s2.f = (float)height;
	m_truetype->m_windowSize.m[0] = width;
	m_truetype->m_windowSize.m[1] = height;

	if (!m_truetype->m_window) return;
	Fc_threadProducer(&m_truetype->m_window->glThread, init);
	if (!m_truetype->m_glyph) return;

	//m_truetype->m_aspect = 1.0 / ((double) width / height);
	m_truetype->m_MVP = FcMatrix4x4_ortho(m_truetype->m_glyph->x_min,
		m_truetype->m_glyph->x_max,
		m_truetype->m_glyph->y_min,
		m_truetype->m_glyph->y_max,
		-1, 1);
}
void FcTrueTypeGL_mouse(unsigned int x, unsigned int y, unsigned int code, void* data0) {
	struct _FcTrueTypeGL_t* m_truetype = data0;
	m_truetype->m_mouse.m[0] = (float)x / (float)m_truetype->m_window->m_width;
	m_truetype->m_mouse.m[1] = (float)y / (float)m_truetype->m_window->m_height;
	Fc_ProducerConsumerData_t init;
	init.id = e_FcGL_callFunction_fff;
	init.s0.v = FcTrueTypeGL_resizeViewport;
	init.s1.f = (float)m_truetype->m_window->m_width;
	init.s2.f = (float)m_truetype->m_window->m_height;
	if (!m_truetype->m_window) return;
	Fc_threadProducer(&m_truetype->m_window->glThread, init);
	if (code == FCWINDOW_MOUSE_LBUTTONDOWN) {
		if (!m_truetype->m_reader) return;
		//printf("l push\n");
		uint16_t id;
		m_truetype->m_unicode++;
		id = m_truetype->m_reader->selectGlyph(m_truetype->m_reader, m_truetype->m_unicode);
		if (m_truetype->m_reader->glyf->ptr_glyph[id].simple.number_contours <= 0)
			return;
		m_truetype->m_glyph = &m_truetype->m_reader->glyf->ptr_glyph[id].simple;

		Fc_ProducerConsumerData_t init;
		init.id = e_FcGL_callFunction_fp;
		init.s0.v = FcTrueTypeGL_copyDataArray;
		init.s1.v = m_truetype;
		init.s2.v = 0;
		Fc_threadProducer(&m_truetype->m_window->glThread, init);

		m_truetype->m_numberVertex = m_truetype->m_glyph->number_points;
		m_truetype->m_MVP = FcMatrix4x4_ortho(m_truetype->m_reader->head->x_min,
			m_truetype->m_reader->head->x_max,
			m_truetype->m_reader->head->y_min,
			m_truetype->m_reader->head->y_max,
			-1, 1);
	}
	else if (code == FCWINDOW_MOUSE_UPWHEEL) {
		/*m_truetype->testMatrixCurve.m[0][0] *= 0.99f;
		m_truetype->testMatrixCurve.m[1][1] *= 0.99f;
		m_truetype->testMatrixCurve.m[0][2] *= 0.99f;
		m_truetype->testMatrixCurve.m[1][2] *= 0.99f;*/
		m_truetype->m_MVP.m[0][0] *= 0.99f;
		m_truetype->m_MVP.m[1][1] *= 0.99f;
		m_truetype->m_MVP.m[0][3] *= 0.99f;
		m_truetype->m_MVP.m[1][3] *= 0.99f;
	}
	else if (code == FCWINDOW_MOUSE_DOWNWHEEL) {
		/*m_truetype->testMatrixCurve.m[0][0] *= 1.01f;
		m_truetype->testMatrixCurve.m[1][1] *= 1.01f;
		m_truetype->testMatrixCurve.m[0][2] *= 1.01f;
		m_truetype->testMatrixCurve.m[1][2] *= 1.01f;*/
		m_truetype->m_MVP.m[0][0] *= 1.01f;
		m_truetype->m_MVP.m[1][1] *= 1.01f;
		m_truetype->m_MVP.m[0][3] *= 1.01f;
		m_truetype->m_MVP.m[1][3] *= 1.01f;
	}
	else if (code == FCWINDOW_MOUSE_MBUTTONDOWN || m_truetype->m_middlePress) {
		if (code == FCWINDOW_MOUSE_MBUTTONDOWN)
			m_truetype->m_middlePress ^= 1;
		GLfloat directionX = m_truetype->m_shiftButtonX - (float)x;
		GLfloat directionY = m_truetype->m_shiftButtonY - (float)y;
		GLfloat norm = sqrt(directionX * directionX + directionY * directionY + 1);
		m_truetype->m_MVP.m[0][3] += (directionX / norm) * 0.01;;
		m_truetype->m_MVP.m[1][3] += (directionY / norm) * 0.01;
		m_truetype->m_shiftButtonX = x;
		m_truetype->m_shiftButtonY = y;
	}
}
GLint FcTrueTypeGL_init(void* window, void* truetype) {
	float* m_ptr;
	uint16_t x, y, i, j;
	FcTrueTypeError m_error = FCGL_TRUETYPE_NOERROR;
	FcGL_Program_parameters_t m_param = { 0 };
	float m_vertex[] = {
			-1, -1,
			-1, +1,
			+1, -1,
			+1, +1
	};
	//float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	double m_maxX = DBL_MIN;
	double m_maxY = DBL_MIN;
	double m_minX = DBL_MAX;
	double m_minY = DBL_MAX;
	FcTrueTypeGL_t* m_truetype = (FcTrueTypeGL_t*)truetype;
	//glEnable(GL_PROGRAM_POINT_SIZE);
	//glEnable(GL_TEXTURE_1D);

	//glEnable(GL_CULL_FACE);
	//glCullFace( GL_BACK);
	//glFrontFace(GL_CW);
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
	//glDepthMask(GL_TRUE);
	//glDepthFunc(GL_ALWAYS);

	m_truetype->m_reader = TrueTypeReader_init(m_truetype->m_font, NULL);
	m_param.typeShaders[0] = FcGL_PROGRAM_VERTEX;
	m_param.typeShaders[1] = FcGL_PROGRAM_FRAGMENT;
	m_param.codeShaders[0] = m_truetype_vertexShader;
	m_param.codeShaders[1] = m_truetype_fragmentShader;

	m_truetype->m_program = FcGL_Program(&m_param);
	if (!m_truetype->m_program.m_program_id) {
		m_error = FCGL_TRUETYPE_PROGRAM;
		goto m_exit;
	}
	m_truetype->m_glyph = &m_truetype->m_reader->glyf->ptr_glyph[m_truetype->m_reader->selectGlyph(m_truetype->m_reader, 0)].simple;
	for (i = 0, y = TrueTypeReader_maxPoints(m_truetype->m_reader); y != 0; i++)
		y >>= i;
	y = 2 << (i + (TrueTypeReader_maxPoints(m_truetype->m_reader) > y));
	glGenTextures(2, m_truetype->m_textureBuffers);

	glBindTexture(GL_TEXTURE_1D, m_truetype->m_textureBuffers[0]);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, y, 0, GL_RGBA, GL_FLOAT, NULL);

	m_ptr = (float*)calloc(1, 4 * y * sizeof(float));
	for (i = 0; i < m_truetype->m_glyph->number_points; i++) {
		m_maxX = m_truetype->m_glyph->parameters[i].x > m_maxX ? m_truetype->m_glyph->parameters[i].x : m_maxX;
		m_minX = m_truetype->m_glyph->parameters[i].x < m_minX ? m_truetype->m_glyph->parameters[i].x : m_minX;
		m_maxY = m_truetype->m_glyph->parameters[i].y > m_maxY ? m_truetype->m_glyph->parameters[i].y : m_maxY;
		m_minY = m_truetype->m_glyph->parameters[i].y < m_minY ? m_truetype->m_glyph->parameters[i].y : m_minY;
	}
	for (i = 0, x = 0; i < m_truetype->m_glyph->number_contours; i++) {
		for (j = m_truetype->m_glyph->endCountours[i]; x <= m_truetype->m_glyph->endCountours[i]; j = x, x++) {
			m_ptr[4 * x + 0] = (1.0 + ((double)m_truetype->m_glyph->parameters[x].x * (2.0 / (m_maxX - m_minX)) - ((m_maxX + m_minX) / (m_maxX - m_minX)))) / 2.0;
			m_ptr[4 * x + 1] = (1.0 + ((double)m_truetype->m_glyph->parameters[x].y * (2.0 / (m_maxY - m_minY)) - ((m_maxY + m_minY) / (m_maxY - m_minY)))) / 2.0;
			m_ptr[4 * x + 2] = (1.0 + ((double)m_truetype->m_glyph->parameters[j].x * (2.0 / (m_maxX - m_minX)) - ((m_maxX + m_minX) / (m_maxX - m_minX)))) / 2.0;
			m_ptr[4 * x + 3] = (1.0 + ((double)m_truetype->m_glyph->parameters[j].y * (2.0 / (m_maxY - m_minY)) - ((m_maxY + m_minY) / (m_maxY - m_minY)))) / 2.0;
		}
	}
	glTexSubImage1D(GL_TEXTURE_1D, 0, 0, m_truetype->m_glyph->number_points, GL_RGBA, GL_FLOAT, m_ptr);

	glBindTexture(GL_TEXTURE_1D, m_truetype->m_textureBuffers[1]);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, y, 0, GL_RGBA, GL_FLOAT, NULL);

	for (i = 0, x = 0; i < m_truetype->m_glyph->number_contours; i++) {
		for (j = m_truetype->m_glyph->endCountours[i]; x <= m_truetype->m_glyph->endCountours[i]; j = x, x++) {
			m_ptr[4 * x + 0] = (1.0 + ((double)m_truetype->m_glyph->parameters[x + 1].x * (2.0 / (m_maxX - m_minX)) - ((m_maxX + m_minX) / (m_maxX - m_minX)))) / 2.0;
			m_ptr[4 * x + 1] = (1.0 + ((double)m_truetype->m_glyph->parameters[x + 1].y * (2.0 / (m_maxY - m_minY)) - ((m_maxY + m_minY) / (m_maxY - m_minY)))) / 2.0;
			m_ptr[4 * x + 2] = m_truetype->m_glyph->m_flags[x] & 1;
			m_ptr[4 * x + 3] = m_truetype->m_glyph->m_flags[j] & 1;
			printf("%d %f %f\n", x, m_ptr[4 * x + 2], m_ptr[4 * x + 3]);
		}
	}

	glTexSubImage1D(GL_TEXTURE_1D, 0, 0, m_truetype->m_glyph->number_points, GL_RGBA, GL_FLOAT, m_ptr);
	glBindTexture(GL_TEXTURE_1D, 0);

	for (i = 0; i < m_truetype->m_glyph->number_points; i++) {
		m_ptr[2 * i + 0] = m_truetype->m_glyph->parameters[i].x;
		m_ptr[2 * i + 1] = m_truetype->m_glyph->parameters[i].y;
	}
	glGenBuffers(2, m_truetype->m_vertexBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_truetype->m_vertexBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, TrueTypeReader_maxPoints(m_truetype->m_reader) * 2 * sizeof(*m_ptr), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, m_truetype->m_glyph->number_points * 2 * sizeof(*m_ptr), m_ptr);

	glBindBuffer(GL_ARRAY_BUFFER, m_truetype->m_vertexBuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertex), m_vertex, GL_STATIC_DRAW);

	glGenBuffers(1, &m_truetype->m_vertexColor);
	glBindBuffer(GL_ARRAY_BUFFER, m_truetype->m_vertexColor);
	glBufferData(GL_ARRAY_BUFFER, TrueTypeReader_maxPoints(m_truetype->m_reader) * 2 * sizeof(float), NULL, GL_STATIC_DRAW);
	for (i = 0; i < m_truetype->m_glyph->number_points; i++) {
		m_ptr[2 * i + 0] = m_truetype->m_glyph->m_flags[i] & 1;
		m_ptr[2 * i + 1] = m_truetype->m_glyph->m_flags[i] & 1;
	}
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_truetype->m_glyph->number_points * 2 * sizeof(float), m_ptr);

	FcGL_Program_bind(&m_truetype->m_program);

	//m_truetype->m_idTestCurve = FcGL_Program_getUniformId(&m_truetype->m_program, "vCurve");
	//m_truetype->m_idTestCurveTransform = FcGL_Program_getUniformId(&m_truetype->m_program, "vCurveTransform");
	m_truetype->m_idVertex = FcGL_Program_getVertexId(&m_truetype->m_program, "vPosition");
	m_truetype->m_idColor = FcGL_Program_getVertexId(&m_truetype->m_program, "vColor");
	m_truetype->m_idTexture[0] = FcGL_Program_getUniformId(&m_truetype->m_program, "textureID");
	m_truetype->m_idTexture[1] = FcGL_Program_getUniformId(&m_truetype->m_program, "textureIDCurve");
	m_truetype->m_idWindow = FcGL_Program_getUniformId(&m_truetype->m_program, "vWindow");
	m_truetype->m_idMVP = FcGL_Program_getUniformId(&m_truetype->m_program, "MVP");
	m_truetype->m_idMouse = FcGL_Program_getUniformId(&m_truetype->m_program, "vMouse");
	m_truetype->m_idSelector = FcGL_Program_getUniformId(&m_truetype->m_program, "vSelector");
	//m_truetype->m_aspect = 1.0 / ((float) m_truetype->m_window->m_height / m_truetype->m_window->m_width);
	m_truetype->m_numberVertex = m_truetype->m_glyph->number_points;
	m_truetype->m_maxVertex = y;
	m_truetype->m_unicode = 32;
	//m_truetype->m_MVP = FcMatrix4x4_identity();
	m_truetype->m_MVP = FcMatrix4x4_ortho(m_truetype->m_glyph->x_min,
		m_truetype->m_glyph->x_max,
		m_truetype->m_glyph->y_min,
		m_truetype->m_glyph->y_max,
		-1, 1);
	//m_truetype->testMatrixCurve = FcMatrix3x3(0.5, 0, 0, 0, 0.5, 0, 0.5f, 0.5f, 1);
	FcTrueTypeGL_testVectors(m_truetype);

	glGenVertexArrays(2, m_truetype->m_VAO);

	glBindVertexArray(m_truetype->m_VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, m_truetype->m_vertexBuffers[1]);
	glEnableVertexAttribArray(m_truetype->m_idVertex);
	glVertexAttribPointer(m_truetype->m_idVertex, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(m_truetype->m_VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, m_truetype->m_vertexBuffers[0]);
	glEnableVertexAttribArray(m_truetype->m_idVertex);
	glVertexAttribPointer(m_truetype->m_idVertex, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_truetype->m_vertexColor);
	glEnableVertexAttribArray(m_truetype->m_idColor);
	glVertexAttribPointer(m_truetype->m_idColor, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glUniform1i(m_truetype->m_idTexture[0], 0);
	glUniform1i(m_truetype->m_idTexture[1], 1);

	glPointSize(10);

	/*m_truetype->testCurve[0][0] = 0;
	m_truetype->testCurve[0][1] = -0.25;
	m_truetype->testCurve[0][2] = 0.00;
	m_truetype->testCurve[0][3] = 1.0;

	m_truetype->testCurve[1][0] = -0.25;
	m_truetype->testCurve[1][1] = 0.00;
	m_truetype->testCurve[1][2] = 0.00;
	m_truetype->testCurve[1][3] = 1.0;

	m_truetype->testCurve[2][0] = 0.0;
	m_truetype->testCurve[2][1] = 0.25;
	m_truetype->testCurve[2][2] = 0.00;
	m_truetype->testCurve[2][3] = 1.0;*/

m_exit:
	if (m_ptr) free(m_ptr);
	return m_error;
}

FcTrueTypeError FcTrueTypeGL_draw(struct _FcTrueTypeGL_t* truetype) {
	uint16_t i, j, m_current;
	float m_selector[2];
	m_selector[0] = truetype->m_numberVertex;
	m_selector[1] = truetype->m_maxVertex;
	//glEnableClientState(GL_VERTEX_ARRAY);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	FcGL_Program_bind(&truetype->m_program);
	glUniformMatrix4fv(truetype->m_idMVP, 1, 0, (const GLfloat*)truetype->m_MVP.m);
	glUniform2fv(truetype->m_idSelector, 1, m_selector);
	glUniform2fv(truetype->m_idWindow, 1, truetype->m_windowSize.m);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_1D, truetype->m_textureBuffers[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_1D, truetype->m_textureBuffers[1]);

	glBindVertexArray(truetype->m_VAO[0]);
	glEnableVertexAttribArray(truetype->m_idVertex);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	m_selector[0] = 0;
	m_selector[1] = 0;
	glUniform2fv(truetype->m_idSelector, 1, m_selector);

	glBindVertexArray(truetype->m_VAO[1]);
	glEnableVertexAttribArray(truetype->m_idVertex);
	glEnableVertexAttribArray(truetype->m_idColor);

	if (truetype->m_glyph->endCountours)
		for (i = 0, j = truetype->m_glyph->endCountours[0], m_current = 0; i < truetype->m_glyph->number_contours; i++) {
			glDrawArrays(GL_LINE_LOOP, m_current, j + 1);
			glDrawArrays(GL_POINTS, m_current, j + 1);
			m_current += j + 1;
			j = truetype->m_glyph->endCountours[i + 1] - truetype->m_glyph->endCountours[i] - 1;
		}

	//glMultiDrawArrays(GL_LINE_LOOP, firstA, countA, m_size);

 //   glDisableVertexAttribArray(truetype->m_idVertex);
	FcGLWindow_swapBuffers(truetype->m_core, truetype->m_window);

	//glDisableClientState(GL_VERTEX_ARRAY);

	//Fc_threadProducer(&truetype->m_window->glThread,
	//                  (Fc_ProducerConsumerData_t) {e_FcGL_callFunction_fp, FcTrueTypeGL_draw, truetype, 0});
}

FcTrueTypeError FcTrueTypeGL_malloc(FcCore_t* core, FcGLWindow_t* window, struct _FcTrueTypeGL_t* truetype, char* font) {
	size_t i;
	FcTrueTypeError m_error = FCGL_TRUETYPE_NOERROR;

	for (i = 0; i < sizeof(FcTrueTypeGL_t); i++) ((uint8_t*)truetype)[i] = 0;
	for (i = 0; font[i]; i++);
	truetype->m_font = malloc(i + 1);
	truetype->m_font[i] = 0;
	while (--i) truetype->m_font[i] = font[i];
	truetype->m_font[i] = font[i];

	truetype->m_core = core;
	truetype->m_window = window;

	FcGLWindow_setCallbackMouse(window, FcTrueTypeGL_mouse, truetype);
	FcGLWindow_setCallbackResizeWindow(window, FcTrueTypeGL_window, truetype, NULL);
	Fc_ProducerConsumerData_t draw_queue_init = {
			e_FcGL_callFunction_fpp, FcTrueTypeGL_init, window, truetype
	};
	Fc_ProducerConsumerData_t draw_queue_draw = {
			e_FcGL_callbackFunction_fp, FcTrueTypeGL_draw, truetype, 0
	};

	Fc_threadProducer(&window->glThread, draw_queue_init);
	Fc_threadProducer(&window->glThread, draw_queue_draw);

	return m_error;
}

FcTrueTypeError FcTrueTypeGL_clear(struct _FcTrueTypeGL_t* truetype) {
	if (truetype->m_VAO[0])
		glDeleteVertexArrays(2, truetype->m_VAO);
	if (truetype->m_textureBuffers[0])
		glDeleteTextures(2, &truetype->m_textureBuffers);
	if (truetype->m_vertexBuffers[0])
		glDeleteBuffers(2, truetype->m_vertexBuffers);
	if (truetype->m_font)
		free(truetype->m_font);
	if (truetype->m_program.m_program_id)
		FcGL_Program_free(&truetype->m_program);
	if (truetype->m_reader)
		TrueTypeReader_free(truetype->m_reader);
}

FcTrueTypeError FcTrueTypeGL_free(struct _FcTrueTypeGL_t* truetype) {
	Fc_ProducerConsumerData_t draw_queue_delete = {
			e_FcGL_callbackFunction_exit, 0, 0, 0
	};
	Fc_ProducerConsumerData_t draw_queue_clear = {
			e_FcGL_callFunction_fp, FcTrueTypeGL_clear, truetype, 0
	};
	Fc_threadProducer(&truetype->m_window->glThread, draw_queue_delete);
	Fc_threadProducer(&truetype->m_window->glThread, draw_queue_clear);

	return FCGL_TRUETYPE_NOERROR;
}