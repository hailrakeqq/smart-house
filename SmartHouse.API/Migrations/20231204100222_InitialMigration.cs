using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace SmartHouse.API.Migrations
{
    /// <inheritdoc />
    public partial class InitialMigration : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_devices_users_UserId",
                table: "devices");

            migrationBuilder.DropIndex(
                name: "IX_devices_UserId",
                table: "devices");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateIndex(
                name: "IX_devices_UserId",
                table: "devices",
                column: "UserId");

            migrationBuilder.AddForeignKey(
                name: "FK_devices_users_UserId",
                table: "devices",
                column: "UserId",
                principalTable: "users",
                principalColumn: "Id",
                onDelete: ReferentialAction.Cascade);
        }
    }
}
