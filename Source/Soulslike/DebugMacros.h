#pragma once

#define DRAW_DEBUG_SPHERE(Location) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 24, FColor::Red, true);
#define DRAW_DEBUG_LINE(StartLoc, EndLoc) if (GetWorld()) DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, true, -1.f, 0, 1.f);
#define DRAW_DEBUG_POINT(Location) if (GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.f, FColor::Red, true);
#define DRAW_DEBUG_VECTOR(StartLoc, EndLoc) if (GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, true, -1.f, 0, 1.f); \
		DrawDebugPoint(GetWorld(), EndLoc, 15.f, FColor::Red, true); \
	}