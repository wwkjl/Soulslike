#pragma once

#define DRAW_DEBUG_SPHERE(Location) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 24, FColor::Red, true);
#define DRAW_DEBUG_SPHERE_COLOR(Location, Color) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 12.f, 24, Color, false, 5.f);
#define DRAW_DEBUG_SPHERE_SINGLE(Location) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 24, FColor::Red, false, -1.f);
#define DRAW_DEBUG_LINE(StartLoc, EndLoc) if (GetWorld()) DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, true, -1.f, 0, 1.f);
#define DRAW_DEBUG_LINE_SINGLE(StartLoc, EndLoc) if (GetWorld()) DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, false, -1.f, 0, 1.f);
#define DRAW_DEBUG_POINT(Location) if (GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.f, FColor::Red, true);
#define DRAW_DEBUG_POINT_SINGLE(Location) if (GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.f, FColor::Red, false, -1.f);
#define DRAW_DEBUG_VECTOR(StartLoc, EndLoc) if (GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, true, -1.f, 0, 1.f); \
		DrawDebugPoint(GetWorld(), EndLoc, 15.f, FColor::Red, true); \
	}
#define DRAW_DEBUG_VECTOR_SINGLE(StartLoc, EndLoc) if (GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, false, -1.f, 0, 1.f); \
		DrawDebugPoint(GetWorld(), EndLoc, 15.f, FColor::Red, false, -1.f); \
	}