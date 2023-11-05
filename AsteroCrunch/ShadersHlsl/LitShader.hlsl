cbuffer cbPerObject : register(b0)
{
    float4x4 gWorld;
};

cbuffer cbPerPass : register(b1)
{
    float4x4 gViewProj;
    float4 gDiffuseAlbedo;
    float4 gLightColor;
    
    float3 gEyePos;
    float3 gLightDir;
    float gRoughness;
    
    
};

struct VertexIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float3 Normal : NORMAL;
    float2 TexCoord : TEXCOORD;
};

struct VertexOut
{
    float4 PosH : SV_POSITION;
    float3 PosW : POSITION;
    float3 NormalW : NORMAL;
    float4 Color : COLOR;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
    
    // Transform to world space.
    float4 posW = mul(float4(vin.Pos, 1.0f), gWorld);
    vout.PosW = posW.xyz;
    
    vout.NormalW = mul(vin.Normal, (float3x3) gWorld);
    //vout.NormalW = vin.Normal;
    
    // Transform to homogeneous clip space.
    vout.PosH = mul(posW, gViewProj);
    
    // Just pass vertex color into the pixel shader.
    vout.Color = vin.Color;
    return vout;
};

float4 PS(VertexOut pin) : SV_Target
{
    // Interpolating normal can unnormalize it, so renormalize it.
    float3 normalized = normalize(pin.NormalW);
    
    float3 toEyeW = normalize(gEyePos - pin.PosW);
    
    float3 ouai = normalize(normalized + toEyeW);
    
    const float shineness = 1.0f - gRoughness;
    
    float4 ambient = gLightColor * gDiffuseAlbedo;
    
    // dot product entre normal et dirLight
    float dotFUCK = clamp(dot(ouai, gLightDir), 0, 1);

    float4 litcolor = (ambient + dotFUCK);
   
    litcolor.a = gDiffuseAlbedo.a;
    
    return litcolor;
    //return gLightColor;
    //return float4(toEyeW, 1.0f);
};