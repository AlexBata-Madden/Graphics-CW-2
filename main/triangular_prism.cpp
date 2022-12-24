#include "triangular_prism.hpp"


   SimpleMeshData make_triangular_prism(Vec3f aSize, float angle, Vec3f aColor, Mat44f aPreTransform)
    {
       
        // 0:       Vec3f { angle, aSize.y/2,aSize.z/2},
        // 1:       Vec3f { aSize.x/2, -aSize.y/2, aSize.z/2},
        // 2:       Vec3f { -aSize.x/2, -aSize.y/2, aSize.z/2},

        // 3:       Vec3f { angle, aSize.y/2, -aSize.z/2},
        // 4:       Vec3f { aSize.x/2, -aSize.y/2, -aSize.z/2},
        // 5:       Vec3f { -aSize.x/2, -aSize.y/2, -aSize.z/2},

        std::vector<Vec3f> pos = {
            
            Vec3f { angle, aSize.y / 2, aSize.z/ 2},
            Vec3f { -aSize.x / 2, -aSize.y / 2, aSize.z / 2},
            Vec3f { aSize.x / 2, -aSize.y / 2, aSize.z / 2},

            Vec3f { angle, aSize.y / 2, -aSize.z / 2},
            Vec3f { aSize.x / 2, -aSize.y / 2, -aSize.z / 2},
            Vec3f { -aSize.x / 2, -aSize.y / 2, -aSize.z / 2},

            Vec3f { angle, aSize.y / 2, -aSize.z / 2},
            Vec3f { -aSize.x / 2, -aSize.y / 2, -aSize.z / 2},
            Vec3f { angle, aSize.y / 2,aSize.z / 2},

            Vec3f { angle, aSize.y / 2,aSize.z / 2},
            Vec3f { -aSize.x / 2, -aSize.y / 2, -aSize.z / 2},
            Vec3f { -aSize.x / 2, -aSize.y / 2, aSize.z / 2},

            Vec3f { angle, aSize.y / 2, -aSize.z / 2},
            Vec3f { angle, aSize.y / 2,aSize.z / 2},
            Vec3f { aSize.x / 2, -aSize.y / 2, aSize.z / 2},

            Vec3f { aSize.x / 2, -aSize.y / 2, aSize.z / 2},
            Vec3f { aSize.x / 2, -aSize.y / 2, -aSize.z / 2},
            Vec3f { angle, aSize.y / 2, -aSize.z / 2},

            Vec3f { -aSize.x / 2, -aSize.y / 2, aSize.z / 2},
            Vec3f { aSize.x / 2, -aSize.y / 2, -aSize.z / 2},
            Vec3f { aSize.x / 2, -aSize.y / 2, aSize.z / 2},

            Vec3f { -aSize.x / 2, -aSize.y / 2, aSize.z / 2},
            Vec3f { -aSize.x / 2, -aSize.y / 2, -aSize.z / 2},
            Vec3f { aSize.x / 2, -aSize.y / 2, -aSize.z / 2},

        };

        Mat33f const N = mat44_to_mat33(transpose(invert(aPreTransform)));

        Vec3f face1 = N * normalise(cross(pos[1] - pos[0], pos[2] - pos[0]));
        Vec3f face2 = N * normalise(cross(pos[4] - pos[3], pos[5] - pos[3]));
        Vec3f face3 = N * normalise(cross(pos[7] - pos[6], pos[8] - pos[6]));
        Vec3f face4 = N * normalise(cross(pos[13] - pos[12], pos[14] - pos[12]));
        Vec3f face5 = N * normalise(cross(pos[19] - pos[18], pos[20] - pos[18]));

        std::vector<Vec3f> norms = {
        face1,face1,face1, 
        face2,face2,face2, 
        face3,face3,face3,
        face3,face3,face3,
        face4,face4,face4,
        face4,face4,face4,
        face5,face5,face5,
        face5,face5,face5,
        };

        std::vector col(pos.size(), aColor);
        std::vector<float> alphas(pos.size(), 1.f);

        for (std::size_t i = 0; i < pos.size(); ++i)
        {
            Vec4f p4{ pos[i].x, pos[i].y, pos[i].z, 1.f };
            Vec4f t = aPreTransform * p4;
            t /= t.w;

            pos[i] = Vec3f{ t.x, t.y, t.z };


        }

        return SimpleMeshData{ std::move(pos), std::move(col), std::move(norms), std::move(alphas)};
}
