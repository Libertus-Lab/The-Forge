/*
 * Copyright (c) 2018-2021 The Forge Interactive Inc.
 *
 * This file is part of The-Forge
 * (see https://github.com/ConfettiFX/The-Forge).
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
*/

#ifndef vb_resources_h
#define vb_resources_h

RES(Tex2D(float4), diffuseMaps[256], UPDATE_FREQ_NONE, t1, binding = 2);
RES(SamplerState, nearClampSampler, UPDATE_FREQ_NONE, s0, binding = 3);
RES(ByteBuffer, indirectMaterialBuffer, UPDATE_FREQ_PER_FRAME, t0, binding = 1);
CBUFFER(objectUniformBlock, UPDATE_FREQ_PER_DRAW, b0, binding = 0)
{
    DATA(float4x4, WorldViewProjMat[VR_MULTIVIEW_COUNT], None);
	DATA(float4x4, WorldMat, None);
};

#if defined(METAL) || defined(DIRECT3D12)
    PUSH_CONSTANT(indirectRootConstant, b2)
    {
        DATA(uint, indirectDrawId, None);
    };
    #define getDrawID() Get(indirectDrawId)
#elif defined(VULKAN) || defined(ORBIS) || defined(PROSPERO)
    #define getDrawID() In.drawId
#endif

DECLARE_RESOURCES()

#endif /* vb_resources_h */