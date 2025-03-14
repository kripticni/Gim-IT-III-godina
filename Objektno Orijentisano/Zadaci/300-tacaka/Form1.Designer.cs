
namespace _300_tacaka
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.crtaj = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // crtaj
            // 
            this.crtaj.Location = new System.Drawing.Point(316, 389);
            this.crtaj.Name = "crtaj";
            this.crtaj.Size = new System.Drawing.Size(125, 44);
            this.crtaj.TabIndex = 0;
            this.crtaj.Text = "crtaj";
            this.crtaj.UseVisualStyleBackColor = true;
            this.crtaj.Click += new System.EventHandler(this.crtaj_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.crtaj);
            this.Name = "Form1";
            this.Text = "Form1";
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Form1_MouseDown);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button crtaj;
    }
}

