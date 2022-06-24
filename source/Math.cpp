#include "external/Catch2.hpp"
#include "Math.hpp"

//? WIP, tests are being added

SCENARIO( "Math vectors can be initalized" ) 
{	
	GIVEN( "Some common values")
	{
		f32 val_x{2.124f}, val_y{3.146f}, val_z{1.269f}, val_w{1.0f};

		WHEN ( "Math vectors initalized by default" )
		{
			lib::Vec2 vec_2 { val_x, val_y };
			lib::Vec3 vec_3 { val_x, val_y, val_z };
			lib::Vec4 vec_4 { val_x, val_y, val_z, val_w };

			THEN( "2D vector should have exact values" )
			{
				REQUIRE( vec_2.x == Approx(val_x) );
				REQUIRE( vec_2.y == Approx(val_y) );

				REQUIRE( vec_2.u == Approx(val_x) );
				REQUIRE( vec_2.v == Approx(val_y) );

				REQUIRE( vec_2.width  == Approx(val_x) );
				REQUIRE( vec_2.height == Approx(val_y) );
			}
			THEN( "3D vector should have exact values" )
			{
				REQUIRE( vec_3.x == Approx(val_x) );
				REQUIRE( vec_3.y == Approx(val_y) );
				REQUIRE( vec_3.z == Approx(val_z) );

				REQUIRE( vec_3.u == Approx(val_x) );
				REQUIRE( vec_3.v == Approx(val_y) );
				REQUIRE( vec_3.w == Approx(val_z) );

				REQUIRE( vec_3.r == Approx(val_x) );
				REQUIRE( vec_3.g == Approx(val_y) );
				REQUIRE( vec_3.b == Approx(val_z) );
			}
			THEN( "4D vector should have exact values" )
			{
				REQUIRE( vec_4.x == Approx(val_x) );
				REQUIRE( vec_4.y == Approx(val_y) );
				REQUIRE( vec_4.z == Approx(val_z) );
				REQUIRE( vec_4.w == Approx(val_w) );

				REQUIRE( vec_4.r == Approx(val_x) );
				REQUIRE( vec_4.g == Approx(val_y) );
				REQUIRE( vec_4.b == Approx(val_z) );
				REQUIRE( vec_4.a == Approx(val_w) );
			}
		}
		WHEN ( "4D Vector is initalized by 3D vector and explicit w" )
		{
			lib::Vec3 vec_3 { val_x, val_y, val_z };
			lib::Vec4 vec_4 { { .xyz = vec_3, .w = val_w } };
			THEN( "4D vector should have exact values" )
			{
				REQUIRE( vec_4.x == Approx(val_x) );
				REQUIRE( vec_4.y == Approx(val_y) );
				REQUIRE( vec_4.z == Approx(val_z) );
				REQUIRE( vec_4.w == Approx(val_w) );

				REQUIRE( vec_4.r == Approx(val_x) );
				REQUIRE( vec_4.g == Approx(val_y) );
				REQUIRE( vec_4.b == Approx(val_z) );
				REQUIRE( vec_4.a == Approx(val_w) );
			}
		}
	}
}

SCENARIO( "Math vectors operators usage" )
{
	GIVEN( "Some vectors and common values" )
	{
		f32 val_x{2.0}, val_y{3.0}, val_z{4.0f}, val_w{1.0f};
		lib::Vec2 vec_2 { val_x, val_y };
		lib::Vec3 vec_3 { val_x, val_y, val_z };
		lib::Vec4 vec_4 { val_x, val_y, val_z, val_w };

		WHEN ( "2D vector operators used" )
		{
			lib::Vec2 temp { 2.0f, 2.0f };
			THEN ( "'-' operator should return proper values" )
			{
				temp = (-vec_2);
				REQUIRE( temp.x == Approx(-val_x) );
				REQUIRE( temp.y == Approx(-val_y) );
			}
			THEN ( "'[]' operator should return a proper value" )
			{
				REQUIRE( vec_2[0] == Approx(val_x) );
				REQUIRE( vec_2[1] == Approx(val_y) );
			}
			THEN ( "'/=' operator should return a proper value" )
			{
				f32 div = 2.0f;
				vec_2 /= div;
				REQUIRE( vec_2.x == Approx(val_x / div) );
				REQUIRE( vec_2.y == Approx(val_y / div) );
			}
			THEN ( "'+=' operator should return a proper value" )
			{
				vec_2 += vec_2;
				REQUIRE( vec_2.x == Approx(val_x + val_x) );
				REQUIRE( vec_2.y == Approx(val_y + val_y) );
			}
			THEN ( "'*=' operator should return a proper value" )
			{
				f32 mul = 2.0f;
				vec_2 *= mul;
				REQUIRE( vec_2.x == Approx(val_x * mul) );
				REQUIRE( vec_2.y == Approx(val_y * mul) );
			}
			THEN ( "'+' operator should return a proper value" )
			{
				lib::Vec2 result = vec_2 + temp;
				REQUIRE( result.x == Approx(vec_2.x + temp.x) );
				REQUIRE( result.y == Approx(vec_2.y + temp.y) );
			}
			THEN ( "'-' operator should return a proper value" )
			{
				lib::Vec2 result = vec_2 - temp;
				REQUIRE( result.x == Approx(vec_2.x - temp.x) );
				REQUIRE( result.y == Approx(vec_2.y - temp.y) );
			}
			THEN ( "'*' operator should return a proper value" )
			{
				lib::Vec2 result = vec_2 * temp;
				REQUIRE( result.x == Approx(vec_2.x * temp.x) );
				REQUIRE( result.y == Approx(vec_2.y * temp.y) );
			}
			THEN ( "'*' operator with scalar should return a proper value" )
			{
				f32 mul = 2.0f;
				lib::Vec2 result = vec_2 * mul;
				REQUIRE( result.x == Approx(vec_2.x * mul) );
				REQUIRE( result.y == Approx(vec_2.y * mul) );
			}
			THEN ( "'/' operator should return a proper value" )
			{
				f32 div = 2.0f;
				lib::Vec2 result = vec_2 / div;
				REQUIRE( result.x == Approx(vec_2.x / div) );
				REQUIRE( result.y == Approx(vec_2.y / div) );
			}
		}
		WHEN ( "3D vector operators used" )
		{
			lib::Vec3 temp { 2.0f, 2.0f, 2.0f };
			THEN ( "'-' operator should return proper values" )
			{
				temp = (-vec_3);
				REQUIRE( temp.x == Approx(-val_x) );
				REQUIRE( temp.y == Approx(-val_y) );
				REQUIRE( temp.z == Approx(-val_z) );
			}
			THEN ( "'[]' operator should return a proper value" )
			{
				REQUIRE( vec_3[0] == Approx(val_x) );
				REQUIRE( vec_3[1] == Approx(val_y) );
				REQUIRE( vec_3[2] == Approx(val_z) );
			}
			THEN ( "'/=' operator should return a proper value" )
			{
				f32 div = 2.0f;
				vec_3 /= div;
				REQUIRE( vec_3.x == Approx(val_x / div) );
				REQUIRE( vec_3.y == Approx(val_y / div) );
				REQUIRE( vec_3.z == Approx(val_z / div) );
			}
			THEN ( "'+=' operator should return a proper value" )
			{
				vec_3 += vec_3;
				REQUIRE( vec_3.x == Approx(val_x + val_x) );
				REQUIRE( vec_3.y == Approx(val_y + val_y) );
				REQUIRE( vec_3.z == Approx(val_z + val_z) );
			}
			THEN ( "'*=' operator should return a proper value" )
			{
				f32 mul = 2.0f;
				vec_3 *= mul;
				REQUIRE( vec_3.x == Approx(val_x * mul) );
				REQUIRE( vec_3.y == Approx(val_y * mul) );
				REQUIRE( vec_3.z == Approx(val_z * mul) );
			}
			THEN ( "'+' operator should return a proper value" )
			{
				lib::Vec3 result = vec_3 + temp;
				REQUIRE( result.x == Approx(vec_3.x + temp.x) );
				REQUIRE( result.y == Approx(vec_3.y + temp.y) );
				REQUIRE( result.z == Approx(vec_3.z + temp.z) );
			}
			THEN ( "'-' operator should return a proper value" )
			{
				lib::Vec3 result = vec_3 - temp;
				REQUIRE( result.x == Approx(vec_3.x - temp.x) );
				REQUIRE( result.y == Approx(vec_3.y - temp.y) );
				REQUIRE( result.z == Approx(vec_3.z - temp.z) );
			}
			THEN ( "'*' operator should return a proper value" )
			{
				lib::Vec3 result = vec_3 * temp;
				REQUIRE( result.x == Approx(vec_3.x * temp.x) );
				REQUIRE( result.y == Approx(vec_3.y * temp.y) );
				REQUIRE( result.z == Approx(vec_3.z * temp.z) );
			}
			THEN ( "'*' operator with scalar should return a proper value" )
			{
				f32 mul = 2.0f;
				lib::Vec3 result = vec_3 * mul;
				REQUIRE( result.x == Approx(vec_3.x * mul) );
				REQUIRE( result.y == Approx(vec_3.y * mul) );
				REQUIRE( result.z == Approx(vec_3.z * mul) );
			}
			THEN ( "'/' operator should return a proper value" )
			{
				f32 div = 2.0f;
				lib::Vec3 result = vec_3 / div;
				REQUIRE( result.x == Approx(vec_3.x / div) );
				REQUIRE( result.y == Approx(vec_3.y / div) );
				REQUIRE( result.z == Approx(vec_3.z / div) );
			}
		}
		WHEN ( "4D vector operators used" )
		{
			lib::Vec4 temp { 2.0f, 2.0f, 2.0f, 1.0f };
			THEN ( "'-' operator should return proper values" )
			{
				temp = (-vec_4);
				REQUIRE( temp.x == Approx(-val_x) );
				REQUIRE( temp.y == Approx(-val_y) );
				REQUIRE( temp.z == Approx(-val_z) );
				REQUIRE( temp.w == Approx(-val_w) );
			}
			THEN ( "'[]' operator should return a proper value" )
			{
				REQUIRE( vec_4[0] == Approx(val_x) );
				REQUIRE( vec_4[1] == Approx(val_y) );
				REQUIRE( vec_4[2] == Approx(val_z) );
				REQUIRE( vec_4[3] == Approx(val_w) );
			}
			THEN ( "'/=' operator should return a proper value" )
			{
				f32 div = 2.0f;
				vec_4 /= div;
				REQUIRE( vec_4.x == Approx(val_x / div) );
				REQUIRE( vec_4.y == Approx(val_y / div) );
				REQUIRE( vec_4.z == Approx(val_z / div) );
				REQUIRE( vec_4.w == Approx(val_w / div) );
			}
			THEN ( "'+=' operator should return a proper value" )
			{
				vec_4 += vec_4;
				REQUIRE( vec_4.x == Approx(val_x + val_x) );
				REQUIRE( vec_4.y == Approx(val_y + val_y) );
				REQUIRE( vec_4.z == Approx(val_z + val_z) );
				REQUIRE( vec_4.w == Approx(val_w + val_w) );
			}
			THEN ( "'*=' operator should return a proper value" )
			{
				f32 mul = 2.0f;
				vec_4 *= mul;
				REQUIRE( vec_4.x == Approx(val_x * mul) );
				REQUIRE( vec_4.y == Approx(val_y * mul) );
				REQUIRE( vec_4.z == Approx(val_z * mul) );
				REQUIRE( vec_4.w == Approx(val_w * mul) );
			}
			THEN ( "'+' operator should return a proper value" )
			{
				lib::Vec4 result = vec_4 + temp;
				REQUIRE( result.x == Approx(vec_4.x + temp.x) );
				REQUIRE( result.y == Approx(vec_4.y + temp.y) );
				REQUIRE( result.z == Approx(vec_4.z + temp.z) );
				REQUIRE( result.w == Approx(vec_4.w + temp.w) );
			}
			THEN ( "'-' operator should return a proper value" )
			{
				lib::Vec4 result = vec_4 - temp;
				REQUIRE( result.x == Approx(vec_4.x - temp.x) );
				REQUIRE( result.y == Approx(vec_4.y - temp.y) );
				REQUIRE( result.z == Approx(vec_4.z - temp.z) );
				REQUIRE( result.w == Approx(vec_4.w - temp.w) );
			}
			THEN ( "'*' operator should return a proper value" )
			{
				lib::Vec4 result = vec_4 * temp;
				REQUIRE( result.x == Approx(vec_4.x * temp.x) );
				REQUIRE( result.y == Approx(vec_4.y * temp.y) );
				REQUIRE( result.z == Approx(vec_4.z * temp.z) );
				REQUIRE( result.w == Approx(vec_4.w * temp.w) );
			}
			THEN ( "'*' operator with scalar should return a proper value" )
			{
				f32 mul = 2.0f;
				lib::Vec4 result = vec_4 * mul;
				REQUIRE( result.x == Approx(vec_4.x * mul) );
				REQUIRE( result.y == Approx(vec_4.y * mul) );
				REQUIRE( result.z == Approx(vec_4.z * mul) );
				REQUIRE( result.w == Approx(vec_4.w * mul) );
			}
			THEN ( "'/' operator should return a proper value" )
			{
				f32 div = 2.0f;
				lib::Vec4 result = vec_4 / div;
				REQUIRE( result.x == Approx(vec_4.x / div) );
				REQUIRE( result.y == Approx(vec_4.y / div) );
				REQUIRE( result.z == Approx(vec_4.z / div) );
				REQUIRE( result.w == Approx(vec_4.w / div) );
			}
		}
	}
}

SCENARIO( "Math vectors functions usage" )
{
	GIVEN( "Some vectors and common values" )
	{
		f32 val_x{2.0}, val_y{3.0}, val_z{4.0f}, val_w{1.0f};
		lib::Vec2 vec_2 { val_x, val_y };
		lib::Vec3 vec_3 { val_x, val_y, val_z };
		lib::Vec4 vec_4 { val_x, val_y, val_z, val_w };

		WHEN ( "2D vector functions used" )
		{
			lib::Vec2 temp { 2.0f, 2.0f };
			THEN ( "dot product should return proper scalar" )
			{
				f32 result = dot(temp, vec_2);
				REQUIRE( result == Approx(10.0f) );
				temp = { 1.0f, 3.0f };
				result = dot(temp, vec_2);
				REQUIRE( result == Approx(11.0f) );
			}
			THEN ( "length should return proper scalar" )
			{
				f32 result = length_vec(vec_2);
				REQUIRE( result == Approx(3.605f).epsilon(0.001) );
				result = length_vec(temp);
				REQUIRE( result == Approx(2.828f).epsilon(0.001) );
			}
			THEN ( "length squared should return proper scalar" )
			{
				f32 result = length_squared_vec(vec_2);
				REQUIRE( result == Approx(13.0f) );
				result = length_squared_vec(temp);
				REQUIRE( result == Approx(8.0f) );
			}
			THEN ( "normalize should return proper vector" )
			{
				lib::Vec2 result = normalize(vec_2);
				REQUIRE( result.x == Approx(0.554f).epsilon(0.01) );
				REQUIRE( result.y == Approx(0.832f).epsilon(0.01) );
				result = normalize(temp);
				REQUIRE( result.x == Approx(0.707f).epsilon(0.01) );
				REQUIRE( result.y == Approx(0.707f).epsilon(0.01) );
			}
			THEN ( "normalize_fast should return proper vector" )
			{
				lib::Vec2 result = normalize_fast(vec_2);
				REQUIRE( result.x == Approx(0.554f).epsilon(0.01) );
				REQUIRE( result.y == Approx(0.832f).epsilon(0.01) );
				result = normalize_fast(temp);
				REQUIRE( result.x == Approx(0.707f).epsilon(0.01) );
				REQUIRE( result.y == Approx(0.707f).epsilon(0.01) );
			}
			THEN ( "perp should return proper vector" )
			{
				lib::Vec2 result = perp(vec_2);
				REQUIRE( result.x == Approx(-val_y) );
				REQUIRE( result.y == Approx(val_x) );
				result = perp(temp);
				REQUIRE( result.x == Approx(-2.0f) );
				REQUIRE( result.y == Approx(2.0f) );
			}
			THEN ( "perp_dot should return proper scalar" )
			{
				f32 result = perp_dot(vec_2, temp);
				REQUIRE( result == Approx(-2.0f) );
				result = perp_dot(temp, vec_2);
				REQUIRE( result == Approx(2.0f) );
			}
			THEN ( "reflect should return proper vector" )
			{
				lib::Vec2 result = reflect(vec_2, temp);
				REQUIRE( result.x == Approx(-38.0f) );
				REQUIRE( result.y == Approx(-37.0f) );
				result = reflect(temp, vec_2);
				REQUIRE( result.x == Approx(-38.0f) );
				REQUIRE( result.y == Approx(-58.0f) );
				result = reflect(vec_2, -vec_2);
				REQUIRE( result.x == Approx(-50.0f) );
				REQUIRE( result.y == Approx(-75.0f) );
			}
			THEN ( "refract should return proper vector" )
			{
				temp = normalize_fast(temp);
				vec_2 = normalize_fast(vec_2);
				f32 ratio = 0.7518f; // air to water
				lib::Vec2 result = refract(vec_2, temp, ratio);
				REQUIRE( result.x == Approx(-0.802f).epsilon(0.01) );
				REQUIRE( result.y == Approx(-0.594f).epsilon(0.01) );
			}
			THEN ( "project should return proper vector" )
			{
				lib::Vec2 result = project(vec_2, temp);
				REQUIRE( result.x == Approx(2.5f) );
				REQUIRE( result.y == Approx(2.5f) );
				result = project(temp, vec_2);
				REQUIRE( result.x == Approx(1.538f).epsilon(0.001) );
				REQUIRE( result.y == Approx(2.307f).epsilon(0.001) );
			}
			THEN ( "project_norm should return proper vector" )
			{
				temp = normalize_fast(temp);
				vec_2 = normalize_fast(vec_2);
				lib::Vec2 result = project_norm(vec_2, temp);
				REQUIRE( result.x == Approx(0.693f).epsilon(0.001) );
				REQUIRE( result.y == Approx(0.693f).epsilon(0.001) );
				result = project_norm(temp, vec_2);
				REQUIRE( result.x == Approx(0.543f).epsilon(0.01) );
				REQUIRE( result.y == Approx(0.815f).epsilon(0.01) );
			}
			THEN ( "project_length should return proper scalar" )
			{
				f32 result = project_length(vec_2, temp);
				REQUIRE( result == Approx(3.535f).epsilon(0.001) );
				result = project_length(temp, vec_2);
				REQUIRE( result == Approx(2.773f).epsilon(0.001) );
			}
			THEN ( "reject should return proper vector" )
			{
				lib::Vec2 result = reject(vec_2, temp);
				REQUIRE( result.x == Approx(-0.5f) );
				REQUIRE( result.y == Approx(0.5f) );
				result = reject(temp, vec_2);
				REQUIRE( result.x == Approx(0.462f).epsilon(0.001) );
				REQUIRE( result.y == Approx(-0.307f).epsilon(0.01) );
			}
			THEN ( "reject_norm should return proper vector" )
			{
				temp = normalize_fast(temp);
				vec_2 = normalize_fast(vec_2);
				lib::Vec2 result = reject_norm(vec_2, temp);
				REQUIRE( result.x == Approx(-0.138f).epsilon(0.01) );
				REQUIRE( result.y == Approx(0.139f).epsilon(0.001) );
				result = reject_norm(temp, vec_2);
				REQUIRE( result.x == Approx(0.164f).epsilon(0.01) );
				REQUIRE( result.y == Approx(-0.108f).epsilon(0.01) );
			}
			THEN ( "reject_length should return proper scalar" )
			{
				f32 result = reject_length(vec_2, temp);
				REQUIRE( result == Approx(0.707f).epsilon(0.001) );
				result = reject_length(temp, vec_2);
				REQUIRE( result == Approx(0.554f).epsilon(0.01) );
			}
		}
	}
}