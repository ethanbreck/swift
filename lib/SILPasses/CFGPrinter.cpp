//===-- CFGPrinter.cpp - CFG printer pass ---------------------------------===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2015 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See http://swift.org/LICENSE.txt for license information
// See http://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//
//
// This file defines external functions that can be called to explicitly
// instantiate the CFG printer.
//
//===----------------------------------------------------------------------===//

#include "swift/SILPasses/Passes.h"
#include "swift/SILPasses/Transforms.h"
#include "swift/SIL/CFG.h"
#include "swift/SIL/SILBasicBlock.h"
#include "swift/SIL/SILInstruction.h"
#include "swift/SIL/SILFunction.h"
#include "llvm/Support/CommandLine.h"

using namespace swift;

//===----------------------------------------------------------------------===//
//                                  Options
//===----------------------------------------------------------------------===//

llvm::cl::opt<std::string>
TargetFunction("view-cfg-only-for-function", llvm::cl::init(""),
               llvm::cl::desc("Only print out the cfg for this function"));

//===----------------------------------------------------------------------===//
//                              Top Level Driver
//===----------------------------------------------------------------------===//

namespace {
class SILCFGPrinter : public SILFunctionTransform {
  StringRef getName() override { return "SIL CFG Printer"; }

  /// The entry point to the transformation.
  void run() override {
    SILFunction *F = getFunction();

    // If we have a target function, only print that function out.
    if (!TargetFunction.empty() && !(F->getName().str() == TargetFunction))
      return;

    F->viewCFG();
  }
};
} // end anonymous namespace

SILTransform *swift::createSILCFGPrinter() { return new SILCFGPrinter(); }
