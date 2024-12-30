# Rasterizer-and-Camera
openGL review Rasterizer and Camera 
## Camera 
GLM Column Major Order 
- View Matrix = View orient * View Tranalte 

        orient[0] = (right.x, up.x, -forward.x, 0.0)

        orient[1] = (right.y, up.y, -forward.y, 0.0)

        orient[2] = (right.z, up.z, -forward.z, 0.0)

        orient[1] = (0.0, 0.0, 0.0, 1.0)

        translate[3] = (-CamerWorldPos.x, -CamerWorldPos.y, -CamerWorldPos.z, 1.0f)

- projection Matrix 

    a = ScreenWidth/ ScreenHeight

    s = 1 / (tan(FOV/2))

    q = -farClip + nearClip/(farClip - nearClip)

    p = farClip /(farClip - nearClip)

        projection[0][0] = 1.0 / (A * tan( radians ( FOV / 2.0f )));

        projection[1][1] = 1.0f / tan( radians ( FOV / 2.0f ));

        projection[2][2] = - farClip/ (farClip - nearClip);
    
        projection[2][3] = - 1.0;

        projection[3][2] = - (farClip *nearClip)/(farClip - nearClip);

## Rasterizer 

- Camera Transformations Vetex:

        World Space vertex * View Matrix to Camera Space 

        Camera Space * Porjection Matrix to Clip Space

        Clip Space / clip.w to Screen Space 

        ((Screen.x Space + 1)/2* width, (1 - Screen.y)/2*height) to Pixel Space 

- Boundbox and isIntersection (Pixel, edge, &x)

- Interpolation 

    Barycentric interpolation 

        vector vA = v0 - v1 

        vector vB = v1 - v2

        v1 = p - v0; v2 = p - v1;  v3 = p - v2;

        area S = 1/2(|vA cross vB|) 

        area s1 = 1/2(|v2 cross v3|); s2 = 1/2(|v1 cross v3|); s3 = 1/2(|v1 cross v3|);

        return {S1/S, S2/S, S3/S}
        
    Perspective coorect interpolation

        overZ (screenV0.z, screenV1.z, screenV2.z)

        correctdBarycentric = (barycentric.x*Overz.x, barycentric.y*Overz.y, barycentric.z*Overz.z);

        sum = correctdBarycentric.x + correctdBarycentric.y + correctdBarycentric.z;

        return correctdBarycentric/sum
    
- depth , Uv and Normal 

        depth = perspABaryCentry.x* screenV0.z + perspABaryCentry.y* screenV1.z + perspABaryCentry.z* screenV2.z;

        uv = perspABaryCentry.x * worldV0.m_uv + perspABaryCentry.y * worldV1.m_uv + perspABaryCentry.z * worldV2.m_uv;

## SSAA

        The core idea of SSAA (Super Sampling Anti-Aliasing) is to render the image at a higher resolution and then downsample it to the target resolution to reduce aliasing.

        I think this is the worst anti-aliasing method. The GPU does significantly more work, but the final output is a smaller image.
    







    
