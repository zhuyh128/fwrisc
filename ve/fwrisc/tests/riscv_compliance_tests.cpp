/*
 * riscv_compliance_tests.cpp
 *
 *
 * Copyright 2018 Matthew Ballance
 *
 * Licensed under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in
 * writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.  See
 * the License for the specific language governing
 * permissions and limitations under the License.
 *
 *  Created on: Oct 24, 2018
 *      Author: ballance
 */

#include "riscv_compliance_tests.h"

void riscv_compliance_tests::SetUp() {
	fprintf(stdout, "SetUp\n");
	fwrisc_instr_tests::SetUp();

	raiseObjection(this);
}

void riscv_compliance_tests::memwrite(uint32_t addr, uint8_t mask, uint32_t data) {
	if (addr == 0x80001000) {
		fprintf(stdout, "Note: end of test\n");
		dropObjection(this);
	} else {
		fwrisc_instr_tests::memwrite((addr&0x0FFFFFFF), mask, data);
	}
}

TEST_F(riscv_compliance_tests, coretest) {
	run();
	fprintf(stdout, "post-test\n");
	for (uint32_t line=0; line<11; line++) {
		for (int32_t word=3; word>=0; word--) {
			uint32_t offset = (0x2030/4)+(4*line)+word;
			fprintf(stdout, "%08x", m_mem[offset].first, offset);
		}
		fprintf(stdout, "\n");
	}
}

TEST_F(riscv_compliance_tests, smoke2) {
	fprintf(stdout, "smoketest2\n");
	run();
}

