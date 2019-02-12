/*------------------------------------------------------------------------
 * Vulkan Conformance Tests
 * ------------------------
 *
 * Copyright (c) 2019 Google LLC
 * Copyright (c) 2019 The Khronos Group Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *//*!
 * \file
 * \brief SPIR-V signed int compare on unsigned scalars values.  Google bug b/73133282
 *//*--------------------------------------------------------------------*/

#include <string>
#include <amber/amber.h>

#include "tcuDefs.hpp"

#include "vktAmberTestCase.hpp"
#include "vktSpvAsmSignedIntCompareTests.hpp"
#include "vktTestGroupUtil.hpp"

namespace vkt
{
namespace SpirVAssembly
{
namespace
{

void createSignedIntCompareTests (tcu::TestCaseGroup* tests, const char* data_dir)
{
	tcu::TestContext& testCtx = tests->getTestContext();

	// Shader test files are saved in <path>/external/vulkancts/data/vulkan/amber/<data_dir>/<basename>.amber
	struct Case {
		const char *basename;
		const char *description;
	};
	const Case cases[] =
	{
		{ "uint_sgreaterthanequal", "32bit unsigned int with OpSGreaterThanEqual" },
		{ "uint_sgreaterthan", "32bit unsigned int with OpSGreaterThan" },
		{ "uint_slessthan", "32bit unsigned int with OpSLessThan" },
		{ "uint_slessthanequal", "32bit unsigned int with OpSLessThanEqual" }
		// For testing fail-to-parse case:
		//, { "foo", "Amber syntax error" }
	};

	for (unsigned i = 0; i < sizeof(cases)/sizeof(cases[0]) ; ++i)
	{

		cts_amber::AmberTestCase *testCase = new cts_amber::AmberTestCase(testCtx, cases[i].basename, cases[i].description);
		// Make sure the input can be parsed before we use it.
		std::string file = std::string(cases[i].basename) + ".amber";
		if (testCase->parse(data_dir, file.c_str()))
		{
			tests->addChild(testCase);
		}
		else
		{
			delete testCase;
			std::string message = "Failed to parse Amber test " + file + ". Check log for details";
			TCU_THROW(Exception, message.c_str());
		}
	}
}

} // anonymous

tcu::TestCaseGroup* createSignedIntCompareGroup (tcu::TestContext& testCtx)
{
	// Location of the Amber script files under the data/vulkan/amber source tree.
	const char* data_dir = "spirv_assembly/instruction/compute/signed_int_compare";
	return createTestGroup(testCtx, "signed_int_compare", "Signed int compare over uint values", createSignedIntCompareTests, data_dir);
}

} // SpirVAssembly
} // vkt
