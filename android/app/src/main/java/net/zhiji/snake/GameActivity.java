package net.zhiji.snake;

import android.app.*;
import android.content.*;
import android.os.*;
import android.provider.*;
import android.widget.*;
import java.io.*;
import java.nio.file.*;
import org.libsdl.app.*;

public class GameActivity extends SDLActivity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		
		// 检查是否已有权限
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
			boolean hasPermission = Environment.isExternalStorageManager();
			if (!hasPermission) {
				// 无权限时跳转设置页
				Intent intent = new Intent(Settings.ACTION_MANAGE_ALL_FILES_ACCESS_PERMISSION);
				startActivity(intent);
				// restartApp(this);
				Toast.makeText(GameActivity.this, "请求授权。", Toast.LENGTH_LONG).show();
			} else {
				File source = new File("/sdcard/Documents/libmain.so");
				File dest   = new File(getFilesDir()+"/libmain.so");
				try
				{
					Files.move(source.toPath(), dest.toPath(), StandardCopyOption.REPLACE_EXISTING);
					source.delete();
					Toast.makeText(GameActivity.this, "移动完成。", Toast.LENGTH_SHORT).show();
				}
				catch (IOException e)
				{
					Toast.makeText(GameActivity.this, "移动失败。", Toast.LENGTH_SHORT).show();
					/*AlertDialog.Builder b = new AlertDialog.Builder(this);
					b.setTitle("错误")
					 .setMessage("移动失败。"+e.toString())
					 .show();*/
					
				}
			}
		} else {
			AlertDialog.Builder b = new AlertDialog.Builder(this);
			b.setTitle("错误")
				.setMessage("系统版本不匹配。")
				.show();
		}
		
		super.onCreate(savedInstanceState);
	}
	
	@Override
	protected void onDestroy()
	{
		super.onDestroy();
		android.os.Process.killProcess(android.os.Process.myPid());
		System.exit(0);
	}
}
